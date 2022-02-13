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
    
    // ToDo : process transmission de résultats à confirmer ou modifier (voir autre todo)
    void receive_results(cpp_int loc_id, std::vector<cpp_int> sums) {
        get_bulletin_board().get_board().push_back( new RegionalBulletin(loc_id, sums[0], sums[1], sums[2]) );
    };

    /**
     * @brief Transmet les résultats régionaux à l'autorité nationale.
     */
    virtual void transmit_results();

    /**
     * @brief Affiche le BulletinBoard d'une autorité sur la sortie standard.
     */
    virtual void print_board();

    /**
     * @brief Effectue le décompte des votes du `board` et l'écrit dans `sums`.
     * ToDo : déplacer make_tally car diffère en fonction du type de bulletin (local ou régional) 
     */
    void make_tally() {
        cpp_int loc_sum_sum = 0;
        cpp_int reg_prod_prod = 1;
        cpp_int nat_prod_prod = 1;
        for (size_t i = 0; i < get_bulletin_board().get_board().size(); i++)  {
            RegionalBulletin* casted_bulletin = (RegionalBulletin*) get_bulletin_board().get_board()[i];
            loc_sum_sum += casted_bulletin->get_loc_sum();
            reg_prod_prod *= casted_bulletin->get_reg_product(); // ToDo : vérifier que c'est bien ces produits là qu'il faut faire (produits trop grands)
            nat_prod_prod *= casted_bulletin->get_nat_product();
        }
        // Insertion des 3 valeurs calculées dans le tableau sums
        get_bulletin_board().get_sums().insert(get_bulletin_board().get_sums().end(), {loc_sum_sum, reg_prod_prod, nat_prod_prod} );
    }

    virtual ~RegionalAuthority() {};
};

#endif // __REGIONAL_AUTHORITY_H
