#ifndef __CENTER_H__
#define __CENTER_H__

#include <boost/multiprecision/cpp_int.hpp>

#include "CryptoUtils.hpp"
#include "BulletinBoard.hpp"

using namespace boost::multiprecision;


/**
 * @file Center.hpp
 * @brief Représente une autorité abstraite.
 */
class Center {

private:
    
    BulletinBoard bulletin_board;
    PublicKey public_key;
    cpp_int private_key;

public:

    // Constructeur
    Center(PublicKey _pkey, cpp_int _skey) : public_key(_pkey), private_key(_skey) {}
    

    /**
     * @brief Renvoie une référence sur le bulletin board.
     * 
     * @return BulletinBoard& une référence sur le bulletin board.
     */
    BulletinBoard& get_bulletin_board() { return bulletin_board; };
    

    /**
    * @brief Renvoie une copie de la clé publique.
    * 
    * @return une copie de la clé publique.
    */
    PublicKey get_public_key() { return public_key; };


    /**
    * @brief Renvoie la clé privée.
    * 
    * @return La clé privée.
    */
    cpp_int get_private_key() { return private_key; };


    /**
     * @brief Transmets le résultat du décompte d'une autorité à sa supérieure hiérarchique.
     * Publie le résultat du vote dans le cas de l'autorité nationale.
     */
    virtual void transmit_results() = 0; // Cette fonction est virtuelle pure et fait de la classe une classe abstraite (non-instanciable)


    /**
     * @brief Affiche le BulletinBoard d'une autorité sur la sortie standard.
     */
    virtual void cout_board() {};


    /**
    * @brief Effectue le décompte des votes.
    */
    virtual void make_tally() = 0;
};

#endif // __CENTER_H__
