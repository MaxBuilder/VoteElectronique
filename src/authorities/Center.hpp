#ifndef __CENTER_H__
#define __CENTER_H__

#include <boost/multiprecision/cpp_int.hpp>

#include "../CryptoUtils.hpp"
#include "../KeyGeneration.hpp"
#include "../Properties.hpp"
#include "../Combiner.hpp"
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
    Combiner *combiner;
    // CryptoManager crypto;

public:
    
    // Constructeur
    Center() {
        std::tuple<PKey, cpp_int> keys = KeyGeneration::generate_keys();
        public_key = std::get<0>(keys);
        private_key = std::get<1>(keys);

        // Génération des serveurs et partage de la clé privée entre ces serveurs
        Properties *prop = Properties::getProperties();
        combiner = new Combiner(private_key, public_key, prop->get_delta(), public_key.N, prop->get_nbServersPerCombiner(), public_key.m);
    }
    

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
    * @brief Renvoie la référence du CryptoManager.
    * 
    * @return la référence du CryptoManager.
    */
    //CryptoManager& get_crypto() { return crypto; }
    Combiner& get_combiner() { return *combiner; };


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
    * @brief Effectue le décompte des votes. Suppose que les votes sont déjà triés : on a supprimé ceux qui étaient invalides.
    */
    virtual void make_tally(cpp_int) = 0;
};

#endif // __CENTER_H__
