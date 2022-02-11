#ifndef __CRYPTO_UTILS_H
#define __CRYPTO_UTILS_H

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;


struct PublicKey {
    cpp_int g;
    cpp_int N;
    cpp_int tetha;      
};

#endif // __CRYPTO_UTILS_H
