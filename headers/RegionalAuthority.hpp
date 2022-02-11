#ifndef __REGIONAL_AUTHORITY_H
#define __REGIONAL_AUTHORITY_H

#include "Center.hpp"
#include "CryptoUtils.hpp"
#include "NationalAuthority.hpp"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;


class RegionalAuthority : public Center {

private:
    int id;
    NationalAuthority& national_auth;

public:
    
    RegionalAuthority(PublicKey _pkey, cpp_int _skey, int _id, NationalAuthority& _national_auth) : Center(_pkey, _skey), id(_id), national_auth(_national_auth) {};

    /**
     * @brief Accesseur à l'attribut id.
     */
    int get_id() { return id; };


    /**
     * @brief Retourne une référence vers l'autorité nationale qui gère l'autorité régionale.
     */
    NationalAuthority& get_national_auth() { return national_auth; };

    /**
     * @brief Transmet les résultats régionaux à l'autorité nationale.
     */
    void transmit_results();


    virtual ~RegionalAuthority() {};
};

#endif // __REGIONAL_AUTHORITY_H
