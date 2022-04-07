#ifndef __LOCALBULLETIN_H__
#define __LOCALBULLETIN_H__

#include <tuple>
#include "../CryptoUtils.hpp"
#include "../Prover.hpp"
#include "Bulletin.hpp"

/**
* Représente le bulletin de vote au niveau local.
*/
class LocalBulletin : public Bulletin {

private:

    // Le timestamp qui doit être apposé par l'autorité lors de la finalisation du vote.
    time_t timestamp;

    // Description du tuple : (chiffré du vote, signature, preuve de validité)
    std::tuple<cpp_int, cpp_int, cpp_int> loc_vote;
    std::tuple<cpp_int, cpp_int, cpp_int> reg_vote;
    std::tuple<cpp_int, cpp_int, cpp_int> nat_vote;
    
    // La preuve d'égalité des chiffrés
    EqProof equ_proof;

    /**
     * @brief Validité du bulletin de vote
     * Vaut 0 si valide, autre valeur si invalide
     */
    int valid;


public:

    // Constructeur
    LocalBulletin(cpp_int pseudo, 
                  time_t timestamp_, 
                  std::tuple<cpp_int, cpp_int, cpp_int> loc_vote_, 
                  std::tuple<cpp_int, cpp_int, cpp_int> reg_vote_, 
                  std::tuple<cpp_int, cpp_int, cpp_int> nat_vote_, 
                  EqProof equ_proof_) :
        Bulletin(pseudo), timestamp(timestamp_), loc_vote(loc_vote_), reg_vote(reg_vote_), nat_vote(nat_vote_), equ_proof(equ_proof_), valid(0) {}


    /**
    * @brief Accesseur sur le timestamp.
    * @return le timestamp.
    */
    time_t get_timestamp();
    

    /**
    * @brief Accesseur sur le vote chiffré avec la clé publique locale.
    * @return le vote chiffré avec la clé publique locale.
    */
    std::tuple<cpp_int, cpp_int, cpp_int> get_loc_vote();


    /**
    * @brief Accesseur sur le vote chiffré avec la clé publique régionale.
    * @return le vote chiffré avec la clé publique régionale.
    */
    std::tuple<cpp_int, cpp_int, cpp_int> get_reg_vote();
    
    
    /**
    * @brief Accesseur sur le vote chiffré avec la clé publique nationale.
    * @return le vote chiffré avec la clé publique nationale.
    */
    std::tuple<cpp_int, cpp_int, cpp_int> get_nat_vote();
    

    /**
    * @brief Accesseur sur la preuve d'égalité des chiffrés.
    */
    EqProof get_equ_proof();

    int get_validity() { return valid; };

    /**
     * @brief Modifie la validité d'un bulletin de vote
     * 
     * @param val 
     */
    void set_validity(int val) { valid = val; };


    /**
    * Affichage du bulletin.
    */
    void cout_board() override;
};

#endif