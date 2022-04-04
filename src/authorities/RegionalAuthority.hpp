#ifndef __REGIONAL_AUTHORITY_H
#define __REGIONAL_AUTHORITY_H

#include "../CryptoUtils.hpp"
#include "Center.hpp"
#include "NationalAuthority.hpp"
#include "../bulletins/NationalBulletin.hpp"
#include "../bulletins/RegionalBulletin.hpp"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

/**
 * @brief Représente un centre d'autorité régional.
 */
class RegionalAuthority : public Center
{

private:
    int id; // L'identifiant du centre régional

    NationalAuthority &national_auth; // La référence sur le centre national dont on dépend

public:
    // Constructeur
    RegionalAuthority(int _id, NationalAuthority &_national_auth) : Center(), id(_id), national_auth(_national_auth){};

    /**
     * @brief Accesseur à l'attribut id.
     */
    int get_id();

    /**
     * @brief Retourne une référence vers l'autorité nationale qui gère l'autorité régionale.
     *
     * @return Center& une référence vers l'autorité nationale qui gère l'autorité régionale.
     */
    NationalAuthority &get_sup_auth();

    /**
     * @brief Transmet les résultats régionaux à l'autorité nationale.
     */
    void transmit_results() override;

    /**
     * @brief Affiche le BulletinBoard d'une autorité sur la sortie standard.
     */
    void cout_board() override;

    void make_tally(cpp_int) override;
};

#endif // __REGIONAL_AUTHORITY_H
