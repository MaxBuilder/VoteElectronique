#ifndef __LOCAL_AUTHORITY_H
#define __LOCAL_AUTHORITY_H

#include "../CryptoUtils.hpp"
#include "Center.hpp"
#include "RegionalAuthority.hpp"
#include "../bulletins/LocalBulletin.hpp"
#include "../bulletins/RegionalBulletin.hpp"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

/**
 * @brief Représente un centre d'autorité local.
 */
class LocalAuthority : public Center
{

private:
    int id; // Identifiant de l'autorité locale

    RegionalAuthority &regional_auth; // Référence sur l'autorité régionale dont on dépend

public:
    // Constructeur
    LocalAuthority(int _id, RegionalAuthority &_regional_auth) : Center(), id(_id), regional_auth(_regional_auth){};

    /**
     * @brief Accesseur sur l'attribut id.
     */
    int get_id();

    /**
     * @brief Retourne une référence vers l'autorité régionale qui gère l'autorité locale.
     *
     * @return Center& une référence vers l'autorité régionale qui gère l'autorité locale.
     */
    RegionalAuthority &get_sup_auth();

    /**
     * @brief Retourne les clés publiques de l'autorité locale et de ses deux autorités supérieures.
     *
     * @return std::array<PublicKey, 3> les clés publiques de l'autorité locale et de ses deux autorités supérieures.
     */
    std::array<PublicKey, 3> get_public_keys();

    /**
     * @brief Transmet les résultats locaux à l'autorité supérieure.
     */
    void transmit_results() override;

    /**
     * @brief Affiche le BulletinBoard d'une autorité sur la sortie standard.
     */
    void cout_board() override;

    void make_tally(cpp_int) override;
};

#endif // __LOCAL_AUTHORITY_H
