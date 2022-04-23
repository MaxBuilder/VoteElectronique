#ifndef __CRYPTO_UTILS_H
#define __CRYPTO_UTILS_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <vector>
#include <boost/integer/mod_inverse.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random/random_device.hpp>

using namespace boost::multiprecision;

typedef struct PublicKey
{
    cpp_int g;
    cpp_int N;
    cpp_int tetha;
    cpp_int beta;
    cpp_int m;
} PKey;

class CryptoUtils
{
public:
    /**
     * @brief Renvoie un cpp_int aléatoire dans Z/NZ \ {0}.
     */
    static cpp_int getRandomZnZ(cpp_int N)
    {
        boost::random_device rn;
        boost::random::mt19937 mt(rn);
        boost::random::uniform_int_distribution<cpp_int> ui(cpp_int(1), cpp_int(N - 1));

        cpp_int res = ui(mt);
        while (true)
        {
            cpp_int q, r;
            boost::multiprecision::divide_qr(N, res, q, r);
            if (r != 0 && res != 1)
                break;
            res = ui(mt);
        }
        return res;
    }


    /*
    * @Brief Génère le vecteur représentant Z/NZ*.
    */
    static std::vector<cpp_int> getInversibleGroup(cpp_int N)
    {
        std::vector<cpp_int> res;
        for (int i = 0; i < N; i++) {
            if (gcd(N, i) == 1)
                res.push_back(i);
        }
        return res;
    }
};

#endif // __CRYPTO_UTILS_H
