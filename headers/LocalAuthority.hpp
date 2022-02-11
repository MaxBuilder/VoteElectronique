#ifndef __LOCAL_AUTHORITY_H
#define __LOCAL_AUTHORITY_H

#include <Center.hpp>
#include <CryptoUtils.hpp>
#include <../headers/RegionalAuthority.hpp>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;



class LocalAuthority : public Center {

private:
    int id;
    RegionalAuthority& regional_auth;

public:

    LocalAuthority(PublicKey _pkey, cpp_int _skey, int _id, RegionalAuthority& _regional_auth) : Center(_pkey, _skey), id(_id), regional_auth(_regional_auth) {};

    /**
    * @brief Accesseur sur l'attribut id.
    */
    int get_id() { return id; };


    /**
     * @brief Retourne une référence vers l'autorité régionale qui gère l'autorité locale.
     * 
     * @return RegionalAuthority& 
     */
    RegionalAuthority& get_regional_auth() { return regional_auth; };


    /**
     * @brief Retourne les clés publiques de l'autorité locale et de ses deux autorités supérieures.
     * 
     * @return std::array<PublicKey, 3> 
     */
    std::array<PublicKey, 3> get_public_keys();


    /**
    * @brief Transmet les résultats locaux à l'autorité supérieure.
    */
    void transmit_results();


    virtual ~LocalAuthority() {};
};

#endif // __LOCAL_AUTHORITY_H
