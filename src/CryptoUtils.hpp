#ifndef __CRYPTO_UTILS_H
#define __CRYPTO_UTILS_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <vector>

using namespace boost::multiprecision;
using namespace boost::random;

typedef struct PublicKey
{
    cpp_int g;
    cpp_int N;
    cpp_int tetha;
    cpp_int beta;
    cpp_int m;
} PKey;


/**
 * @brief Renvoie un cpp_int aléatoire dans Z/NZ*
 * 
 * @return cpp_int un cpp_int aléatoire dans Z/NZ*.
 */
cpp_int getRandomZnZ(PKey PK) {

    mt19937 mt;
    uniform_int_distribution<cpp_int> ui(cpp_int(1), cpp_int(PK.N - 1));

    cpp_int res = 0;
    do {
        res = ui(mt);
    } while (res == 0);

    return res;
}

#endif // __CRYPTO_UTILS_H
