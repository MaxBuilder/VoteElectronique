#ifndef __CRYPTO_UTILS_H
#define __CRYPTO_UTILS_H

#include <boost/multiprecision/cpp_int.hpp>
#include <vector>

using namespace boost::multiprecision;

typedef struct PublicKey
{
    cpp_int g;
    cpp_int N;
    cpp_int tetha;
} PKey;


/**
* @Brief Algorithme de Horner permettant l'�valuation rapide d'un polyn�me.
* 
* @return cpp_int l'�valuation du polyn�me P de rang n avec la valeur x.
*/
/*cpp_int horner(cpp_int poly[], int n, cpp_int x)
{
    cpp_int result = poly[0];

    for (int i = 1; i < n; i++) {
        boost::multiprecision::multiply(result, result, x);
        boost::multiprecision::add(result, result, poly[i]);
    }

    return result;
}*/

#endif // __CRYPTO_UTILS_H
