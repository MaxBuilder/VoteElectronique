#include "headers/Properties.hpp"
#include "headers/Center.hpp"
#include "headers/NationalAuthority.hpp"
#include "headers/RegionalAuthority.hpp"
#include "headers/LocalAuthority.hpp"

#include "headers/Verifier.hpp"
#include <chrono>
#include <ctime>
int main(int argc, char const *argv[])
{
    std::cout << "\033[0;32mTest de la gestion des durées\033[0m\n";

    Properties *prop = Properties::getProperties();
    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    prop->setVoteStart(start_time);

    // Calcule le timestamp de fin de vote
    double voteDuration = prop->getVoteDuration();
    std::time_t end_time = start_time + voteDuration/1000;
    prop->setVoteEnd(end_time);
    std::cout << "Durée du vote: " << voteDuration/1000 << "s | " << voteDuration/1000/60 << "mn | " << voteDuration/1000/60/60 << "h\n";
    std::cout << "Début: " << start_time << " | " << std::ctime(&(start_time))
              << "Fin  : " << end_time << " | " << std::ctime(&end_time) << "\n";
    

    std::cout << "\033[0;32mSimulation de transmission d'un (faux) tableau Sums des autorités locales vers les régionales\033[0m\n";

    int nb_voters = prop->get_nbRegionalAuth() * prop->get_nbLocalPerRegionalAuth() * 3; // 3 électeurs par autorité locale
    cpp_int M = pow(cpp_int(2), ceil(log2(nb_voters)));                                  // 2^ln(l)


    // Création de l'autorité nationale
    NationalAuthority nat_auth;
    // Génération des autorités régionales
    std::vector<RegionalAuthority> reg_auths;
    for (int i = 0; i < prop->get_nbRegionalAuth(); i++)  {
        reg_auths.push_back(RegionalAuthority(i + 1, nat_auth));
    }

    // Génération des autorités locales
    std::vector<LocalAuthority> loc_auths;
    for (size_t i = 0; i < reg_auths.size(); i++)  {
        for (int j = 0; j < prop->get_nbLocalPerRegionalAuth(); j++)  {
            loc_auths.push_back(LocalAuthority(j + 1, reg_auths[i]));
        }
    }


    // Générations de votes aléatoires non chiffrés dans les boards des autorités locales
    cpp_int fake_vote;
    std::tuple<cpp_int, cpp_int, cpp_int> fake_vote_tuple;
    for (size_t i = 0; i < loc_auths.size(); i++)  {
        for (size_t j = 0; j < 3; j++)  {   
            sleep(1);                                             // 3 électeurs par autorité locale
            fake_vote = pow(M, rand() % prop->get_nbCandidats() + 1);       // Vote: M^mi
            fake_vote_tuple = {fake_vote, fake_vote, fake_vote}; // ToDo: chiffrement, signature et preuve de validité du vote
            loc_auths[i].get_bulletin_board().get_board().push_back(
                new LocalBulletin(j, time(nullptr), fake_vote_tuple, fake_vote_tuple, fake_vote_tuple, cpp_int(0)));
        }
    }

    // Filtrage des boards par timestamp
    for  (size_t i = 0; i < loc_auths.size(); i++) {
        if (Verifier::check_timestamp(loc_auths[i].get_bulletin_board().get_board())) {
            std::cout << "Vote frauduleux sur le board de l'autorité locale " << i+1 << "\n";
        }
    }

    // Tally des sommes locales et cout des tableaux locaux pour vérification
    for (size_t i = 0; i < loc_auths.size(); i++)  {
        loc_auths[i].make_tally(loc_auths[i].get_public_key().N);
        loc_auths[i].cout_board();
    }

    std::cout << "\n\n";

    // Transmettre aux régionales
    for (size_t i = 0; i < loc_auths.size(); i++)  {
        loc_auths[i].transmit_results();
    }

    // Tally des sommes régionales et cout des tableaux régionaux pour vérification
    for (size_t i = 0; i < reg_auths.size(); i++)  {
        reg_auths[i].make_tally(reg_auths[i].get_public_key().N);
        reg_auths[i].cout_board();
    }

    // Transmettre à la nationale
    for (size_t i = 0; i < reg_auths.size(); i++)  {
        reg_auths[i].transmit_results();
    }

    // Tally des sommes nationales
    nat_auth.make_tally(nat_auth.get_public_key().N);
    
    // Print du tableau national pour vérifier 
    std::cout << "\n\033[01;34mShowing national authority\n\033[00m";
    nat_auth.cout_board();


    // ToDo : scénario sans chiffrement (simplement avec M^candidat)

    return 0;
}
