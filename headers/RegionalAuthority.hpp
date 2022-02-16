#ifndef __REGIONAL_AUTHORITY_H
#define __REGIONAL_AUTHORITY_H

#include "Center.hpp"
#include "CryptoUtils.hpp"
#include "NationalAuthority.hpp"
#include "RegionalBulletin.hpp"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;


class RegionalAuthority : public Center {

private:
    int id;
    NationalAuthority& national_auth;

public:
    
    RegionalAuthority(PublicKey _pkey, cpp_int _skey, int _id, NationalAuthority& _national_auth) : 
                      Center(_pkey, _skey), id(_id), national_auth(_national_auth) {};

    /**
     * @brief Accesseur à l'attribut id.
     */
    int get_id() { return id; };


    /**
     * @brief Retourne une référence vers l'autorité nationale qui gère l'autorité régionale.
     */
    NationalAuthority& get_national_auth() { return national_auth; };
    
    /**
     * @brief Reçoit le tableau des sommes et produit d'une autorité locale et le marque dans le BulletinBoard
     * 
     * @param loc_id ID (pseudonym) de l'autorité locale
     * @param sums   Tableau des sommes et produits que l'autorité locale transmet
     * ToDo : process transmission de résultats à confirmer ou modifier (voir autre todo)
     */
    void receive_results(cpp_int loc_id, std::vector<cpp_int> sums);

    /**
     * @brief Effectue le décompte des votes du `board` et l'écrit dans `sums`.
     * ToDo : déplacer make_tally car diffère en fonction du type de bulletin (local ou régional) 
     */
    void make_tally();

    /**
     * @brief Transmet les résultats régionaux à l'autorité nationale.
     */
    virtual void transmit_results();

    /**
     * @brief Affiche le BulletinBoard d'une autorité sur la sortie standard.
     */
    virtual void print_board();

    virtual ~RegionalAuthority() {};
};

#endif // __REGIONAL_AUTHORITY_H
