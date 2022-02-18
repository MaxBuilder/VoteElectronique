#include "headers/Center.hpp"
#include "headers/NationalAuthority.hpp"
#include "headers/RegionalAuthority.hpp"
#include "headers/LocalAuthority.hpp"

int main(int argc, char const *argv[])  {
    std::cout << "\033[0;32mSimulation de transmission d'un (faux) tableau Sums des autorités locales vers les régionales\033[0m\n";
    // Config de base (nombre de régionales et locales)
    int nb_reg = 3; // 3 régionales
    int nb_loc_per_reg = 2; // 2 locales par régionales

    PublicKey _pkey = {};
    cpp_int _skey = 8;
    NationalAuthority nat_auth(_pkey, _skey);
        // Génère ses clés publiques
        // Lis le fichier config
        // Génère le nombre de régionales qu'il faut
            // 

    std::vector<RegionalAuthority> reg_auths;
    for (int i = 0; i < nb_reg; i++)  {
        reg_auths.push_back( RegionalAuthority(_pkey, _skey, i+1, nat_auth) );
    }
    
    std::vector<LocalAuthority> loc_auths;
    for (size_t i = 0; i < reg_auths.size(); i++)  {
        for (int j = 0; j < nb_loc_per_reg; j++)  {
            loc_auths.push_back( LocalAuthority(_pkey, _skey, j+1, reg_auths[i]) );
        }
    }
    
    // Tester de remplir les sums des locales, puis de les écrire dans regionale puis de les écrire dans nationale
    for (size_t i = 0; i < loc_auths.size(); i++)  {
        // Remplissage des tableaux sums avec 3 valeurs aléatoires 
        for (size_t j = 0; j < 3; j++)  {
            loc_auths[i].get_bulletin_board().get_sums().push_back(rand() % 100 + 1);
        }
    }

    // Print les tableaux locaux et vérifier 
    for (size_t i = 0; i < loc_auths.size(); i++)  {
        std::cout << "\033[0;33mShowing loc authority " << loc_auths[i].get_sup_auth().get_id() << ", " << loc_auths[i].get_id() << "\n\033[00m";
        loc_auths[i].cout_board();
    }

    std::cout << "\n";

    // Transmettre aux régionales
    for (size_t i = 0; i < loc_auths.size(); i++)  {
        loc_auths[i].transmit_results();
    }

    // Tally des sommes régionales
    for (size_t i = 0; i < reg_auths.size(); i++)  {
        reg_auths[i].make_tally();
    }

    std::cout << "\n";

    // Print les tableaux régionaux et vérifier 
    for (size_t i = 0; i < reg_auths.size(); i++)  {
        std::cout << "\033[0;33mShowing reg authority " << reg_auths[i].get_id() << "\n\033[00m";
        reg_auths[i].cout_board();
    }

    // Transmettre à la nationale
    for (size_t i = 0; i < reg_auths.size(); i++)  {
        reg_auths[i].transmit_results();
    }

    // Tally des sommes nationales
    nat_auth.make_tally();
    
    // Print du tableau national pour vérifier 
    std::cout << "\n\033[01;34mShowing national authority\n\033[00m";
    nat_auth.cout_board();


    // ToDo : scénario sans chiffrement (simplement avec M^candidat)
    
    return 0;
}
