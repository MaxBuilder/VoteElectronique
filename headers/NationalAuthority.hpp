#ifndef __NATIONAL_AUTHORITY_H__
#define __NATIONAL_AUTHORITY_H__

#include "Center.hpp"

class NationalAuthority : public Center {

private:
    
public:
    NationalAuthority(PublicKey _pkey, cpp_int _skey) : Center(_pkey, _skey) {}
    
    /**
     * @brief Annonce les résultats de l'élection.
     */
    void transmit_results();


    virtual ~NationalAuthority() {};
};

#endif // __NATIONAL_AUTHORITY_H__
