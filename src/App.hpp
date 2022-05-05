#ifndef __APP_H
#define __APP_H 

#include <chrono>
#include <ctime>

#include "Properties.hpp"
#include "CryptoUtils.hpp"
#include "Encryption.hpp"

#include "authorities/Center.hpp"
#include "authorities/NationalAuthority.hpp"
#include "authorities/RegionalAuthority.hpp"
#include "authorities/LocalAuthority.hpp"

#include "Client.hpp"

class App {
private:
    NationalAuthority nat_auth;
    std::vector<RegionalAuthority> reg_auths;
    std::vector<LocalAuthority> loc_auths;

    int nb_voters;
    int nb_authorities;
    cpp_int M;

protected:
	static App *reference; // Le pointeur sur l'unique objet (DP Singleton)

	// Constructeur protégé
	App();

public:
    
    App(App &other) = delete; // Pas clonable
	void operator=(const App&) = delete; // Pas de construction de copie par affectation

    /**
	 * @brief App Singleton: S'assure qu'il y a toujours une unique instance de la classe.
	 * Renvoie la référence vers l'objet s'il existe, ou bien le crée dans le cas contraire.
	 */
	static App *getApp();

    // Accesseurs
    NationalAuthority& get_nat_auth() { return nat_auth; };
    std::vector<RegionalAuthority>& get_reg_auths() { return reg_auths; };
    std::vector<LocalAuthority>& get_loc_auths() { return loc_auths; };

    // Instanciation des autorités régionales et locales
    void instanciate_authorities();

    // Génération de votes aléatoires chiffrés dans les boards des autorités locales
    void generate_random_votes();

    // Filtrage des bulletins locaux par timestamp, signature, preuve de vote et preuve d'égalité
    void filter_local_boards();

    // Décompte des bulletins locaux et publication des résultats sur les boards régionaux
    void compute_local_tallies_and_transmission();

    // Décompte des bulletins régionaux et publication des résultats sur le board national
    void compute_regional_tallies_and_transmission();
    
    // Décompte des bulletins nationaux
    void compute_national_tally();
    
    // Extraction des résultats du vote à partir du décompte total déchiffré
    void publish_vote_results();
};

#endif // __APP_H


