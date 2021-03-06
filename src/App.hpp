#ifndef __APP_H
#define __APP_H 

#include <chrono>
#include <ctime>

#include "Properties.hpp"
#include "cryptosystem/Encryption.hpp"
#include "Verifier.hpp"
#include "Prover.hpp"
#define BITSIZE 8

#include "authorities/Center.hpp"
#include "authorities/NationalAuthority.hpp"
#include "authorities/RegionalAuthority.hpp"
#include "authorities/LocalAuthority.hpp"


typedef struct EncryptedVote {
        CryptoUtils::PKeyRSA pkey;
        std::tuple<cpp_int, cpp_int, cpp_int> localVote;
        std::tuple<cpp_int, cpp_int, cpp_int> regionalVote;
        std::tuple<cpp_int, cpp_int, cpp_int> nationalVote;
        // ToDo: legal_vote_proof
        EqProof eq_proof;
} EncryptedVote;

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
    void instanciate_authorities(bool verbose);

    

    // Méthodes de vote à exécuter par les électeurs
    CryptoUtils::SKeyRSA generateVoterKeys();
    cpp_int signRSA(cpp_int message, CryptoUtils::SKeyRSA sk);

    /**
     * @brief 
     * 
     * @param pkeys         Clés publiques des autorités locales, régionales et nationales
     * @param M 
     * @param vote 
     */
    EncryptedVote vote(std::array<PublicKey, 3> pkeys, cpp_int M, int vote);

    // Génération de votes aléatoires chiffrés dans les boards des autorités locales
    void generate_random_votes();

    // Génération de votes issus de la configuration dans les boards des autorités locales
    void read_vote_file();

    // Filtrage des bulletins locaux par timestamp, signature, preuve de vote et preuve d'égalité
    void filter_local_boards();

    // Décompte des bulletins locaux et publication des résultats sur les boards régionaux
    void compute_local_tallies_and_transmission(bool verbose);

    // Décompte des bulletins régionaux et publication des résultats sur le board national
    void compute_regional_tallies_and_transmission(bool verbose);
    
    // Décompte des bulletins nationaux
    void compute_national_tally(bool verbose);
    
    // Extraction des résultats du vote à partir du décompte total déchiffré
    void publish_vote_results();
};

#endif // __APP_H


