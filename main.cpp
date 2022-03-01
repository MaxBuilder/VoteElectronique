#include "../headers/Properties.hpp"
#include "headers/Center.hpp"
#include "headers/NationalAuthority.hpp"
#include "headers/RegionalAuthority.hpp"
#include "headers/LocalAuthority.hpp"

// Config de base (nombre de régionales et locales)

#define nb_candidats 3

int main(int argc, char const *argv[])  {
    std::cout << "\033[0;32mSimulation de transmission d'un (faux) tableau Sums des autorités locales vers les régionales\033[0m\n";

    Properties prop = Properties::getProperties();

    int nb_voters = prop.get_nbRegionalAuth() * prop.get_nbLocalPerRegionalAuth() * 3; // 3 électeurs par autorité locale 
    cpp_int M = pow( cpp_int(2), ceil(log2(nb_voters)) ); // 2^ln(l)

    // Fausses clés pour la création
    PublicKey _pkey = { 0, 90, 0 };
    cpp_int _skey = 8;

    // Création de l'autorité nationale
    NationalAuthority nat_auth(_pkey, _skey);
        
    // Génération des autorités régionales
    std::vector<RegionalAuthority> reg_auths;
    for (int i = 0; i < prop.get_nbRegionalAuth(); i++)  {
        reg_auths.push_back( RegionalAuthority(_pkey, _skey, i+1, nat_auth) );
    }
    
    // Génération des autorités locales
    std::vector<LocalAuthority> loc_auths;
    for (size_t i = 0; i < reg_auths.size(); i++)  {
        for (int j = 0; j < prop.get_nbLocalPerRegionalAuth(); j++)  {
            loc_auths.push_back( LocalAuthority(_pkey, _skey, j+1, reg_auths[i]) );
        }
    }
    
    // Générations de votes aléatoires non chiffrés dans les boards des autorités locales
    cpp_int fake_vote;
    std::tuple<cpp_int, cpp_int, cpp_int> fake_vote_tuple;
    for (size_t i = 0; i < loc_auths.size(); i++)  {
        for (size_t j = 0; j < 3; j++)  { // 3 électeurs par autorité locale
            fake_vote = pow(M, rand() % nb_candidats + 1); // Vote: M^mi
            fake_vote_tuple = {fake_vote, fake_vote, fake_vote}; // ToDo: chiffrement, signature et preuve de validité du vote
            loc_auths[i].get_bulletin_board().get_board().push_back( 
                new LocalBulletin(j, time(nullptr), fake_vote_tuple, fake_vote_tuple, fake_vote_tuple, cpp_int(0) ) );
        }
    }

    // Tally des sommes locales et cout des tableaux locaux pour vérification
    for (size_t i = 0; i < loc_auths.size(); i++)  {
        loc_auths[i].make_tally(_pkey.N);
        loc_auths[i].cout_board();
    }

    std::cout << "\n\n";

    // Transmettre aux régionales
    for (size_t i = 0; i < loc_auths.size(); i++)  {
        loc_auths[i].transmit_results();
    }

    // Tally des sommes régionales et cout des tableaux régionaux pour vérification
    for (size_t i = 0; i < reg_auths.size(); i++)  {
        reg_auths[i].make_tally(_pkey.N);
        reg_auths[i].cout_board();
    }

    // Transmettre à la nationale
    for (size_t i = 0; i < reg_auths.size(); i++)  {
        reg_auths[i].transmit_results();
    }

    // Tally des sommes nationales
    nat_auth.make_tally(_pkey.N);
    
    // Print du tableau national pour vérifier 
    std::cout << "\n\033[01;34mShowing national authority\n\033[00m";
    nat_auth.cout_board();


    // ToDo : scénario sans chiffrement (simplement avec M^candidat)
    
    return 0;
}
