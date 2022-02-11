#include "headers/Center.hpp"
#include "headers/NationalAuthority.hpp"
#include "headers/RegionalAuthority.hpp"
#include "headers/LocalAuthority.hpp"

int main(int argc, char const *argv[])  {
    std::cout << "Start" << std::endl;
    
    // Créer une autorité nationale
    // Qui génère des régionales et des locales

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
        reg_auths.push_back( RegionalAuthority(_pkey, _skey, i, nat_auth) );
    }
    
    std::vector<LocalAuthority> loc_auths;
    for (size_t i = 0; i < reg_auths.size(); i++)  {
        for (int j = 0; j < nb_loc_per_reg; j++)  {
            loc_auths.push_back( LocalAuthority(_pkey, _skey, j, reg_auths[i]) );
        }
    }
    
    // Tester de remplir les sums des locales, puis de les écrire dans regionale puis de les écrire dans nationale
    // Print tous les tableaux et vérifier 
    for (size_t i = 0; i < loc_auths.size(); i++)  {
        // Remplissage des tableaux sums avec 3 valeurs aléatoires 
        for (size_t j = 0; j < 3; j++)  {
            loc_auths[i].get_board().get_sums().push_back(9);
        }

        std::cout << "Autorité " << loc_auths[i].get_regional_auth().get_id() << ", " << loc_auths[i].get_id() << std::endl;
    }

    return 0;
}
