#ifndef __ENCRYPTION_H
#define __ENCRYPTION_H

#include <boost/multiprecision/cpp_int.hpp>
#include "CryptoUtils.hpp"

using namespace boost::multiprecision;

class Encryption {
public:

    /**
     * @brief Chiffrement de Pailler
     * 
     * @param PK
     * @param M
     * @return cpp_int 
     */
    static CipherStruct encrypt(PKey PK, cpp_int M);

};

#endif
