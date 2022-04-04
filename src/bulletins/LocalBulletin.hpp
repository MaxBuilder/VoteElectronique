#ifndef __LOCALBULLETIN_H__
#define __LOCALBULLETIN_H__

#include <tuple>
#include "Bulletin.hpp"

/**
* Repr�sente le bulletin de vote au niveau local.
*/
class LocalBulletin : public Bulletin {

private:

    // Le timestamp qui doit �tre appos� par l'autorit� lors de la finalisation du vote.
    time_t timestamp;

    // Description du tuple : (chiffr� du vote, signature, preuve de validit�)
    std::tuple<cpp_int, cpp_int, cpp_int> loc_vote;
    std::tuple<cpp_int, cpp_int, cpp_int> reg_vote;
    std::tuple<cpp_int, cpp_int, cpp_int> nat_vote;
    
    // La preuve d'�galit� des chiffr�s
    cpp_int equ_proof = -1;


public:

    // Constructeur
    LocalBulletin(cpp_int pseudo, time_t timestamp_, std::tuple<cpp_int, cpp_int, cpp_int> loc_vote_, std::tuple<cpp_int, cpp_int, cpp_int> reg_vote_, std::tuple<cpp_int, cpp_int, cpp_int> nat_vote_, cpp_int equ_proof_) :
        Bulletin(pseudo), timestamp(timestamp_), loc_vote(loc_vote_), reg_vote(reg_vote_), nat_vote(nat_vote_), equ_proof(equ_proof_) {}


    /**
    * @brief Accesseur sur le timestamp.
    * @return le timestamp.
    */
    time_t get_timestamp();
    

    /**
    * @brief Accesseur sur le vote chiffr� avec la cl� publique locale.
    * @return le vote chiffr� avec la cl� publique locale.
    */
    std::tuple<cpp_int, cpp_int, cpp_int> get_loc_vote();


    /**
    * @brief Accesseur sur le vote chiffr� avec la cl� publique r�gionale.
    * @return le vote chiffr� avec la cl� publique r�gionale.
    */
    std::tuple<cpp_int, cpp_int, cpp_int> get_reg_vote();
    
    
    /**
    * @brief Accesseur sur le vote chiffr� avec la cl� publique nationale.
    * @return le vote chiffr� avec la cl� publique nationale.
    */
    std::tuple<cpp_int, cpp_int, cpp_int> get_nat_vote();
    

    /**
    * @brief Accesseur sur la preuve d'�galit� des chiffr�s.
    */
    cpp_int get_equ_proof();


    /**
    * Affichage du bulletin.
    */
    void cout_board() override;
};

#endif