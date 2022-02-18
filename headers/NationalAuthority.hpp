#ifndef __NATIONAL_AUTHORITY_H__
#define __NATIONAL_AUTHORITY_H__

#include "Center.hpp"

/**
* @brief Représente le centre national d'autorité.
*/
class NationalAuthority : public Center {
    

public:

    // Constructeur
    NationalAuthority(PublicKey _pkey, cpp_int _skey) : Center(_pkey, _skey) {}
    

    /**
     * @brief Annonce les résultats de l'élection.
     */
    void transmit_results() override;


    /**
     * @brief Affiche le BulletinBoard d'une autorité sur la sortie standard.
     */
    void cout_board() override;
    

    /**
     * @brief Effectue le décompte des votes.
     */
    void make_tally() override;
};

#endif // __NATIONAL_AUTHORITY_H__
