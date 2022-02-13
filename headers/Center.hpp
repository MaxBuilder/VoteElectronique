#ifndef __CENTER_H__
#define __CENTER_H__

#include <boost/multiprecision/cpp_int.hpp>

#include "CryptoUtils.hpp"
#include "BulletinBoard.hpp"


/**
 * @file Center.hpp
 * @brief Représente une autorité.
 */

using namespace boost::multiprecision;

class Center {

private:
    
    BulletinBoard bulletin_board;
    PublicKey public_key;
    cpp_int private_key;

public:

    Center(PublicKey _pkey, cpp_int _skey) : public_key(_pkey), private_key(_skey) {}
    
    /**
     * @brief Get the board object
     * 
     * @return BulletinBoard 
     */
    BulletinBoard& get_bulletin_board() { return bulletin_board; };
    
    PublicKey get_public_key() { return public_key; };
    cpp_int get_private_key() {return private_key; };

    /**
     * @brief Vérifie la justesse du vote sur le board d'une autorité.
     * 
     * @return true si le vote est juste
     * @return false si non
     */
    bool check_vote() {
        bulletin_board.verify();
        return 0; // ToDo
    };

    /**
     * @brief Transmets le résultat du décompte d'une autorité à sa supérieure hiérarchique.
     * Publie le résultat du vote dans le cas de l'autorité nationale.
     */
    virtual void transmit_results() {};

    /**
     * @brief Affiche le BulletinBoard d'une autorité sur la sortie standard.
     */
    virtual void print_board() {};

    virtual ~Center() {};
};

#endif // __CENTER_H__
