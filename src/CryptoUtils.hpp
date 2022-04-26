#ifndef __CRYPTO_UTILS_H
#define __CRYPTO_UTILS_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include <vector>
#include <boost/integer/mod_inverse.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random/random_device.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "sha256.hpp"
#include <boost/integer/mod_inverse.hpp>

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


    static cpp_int sha256(const std::string& str)
    {
        // unsigned char hash[32];
        // SHA256_CTX sha256;
        // SHA256_Init(&sha256);
        // SHA256_Update(&sha256, str.c_str(), str.size());
        // SHA256_Final(hash, &sha256);
        
        std::string hash = sha256_stack(str);

        std::stringstream ss;
        for (int i = 0; i < 32; i++)
        {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }

        std::string pre_res = ss.str();
        cpp_int res = 0;
        for (int i = pre_res.length() - 1; i >= 0; i--)
        {
            cpp_int tmp;
            char c = pre_res.at(i);
            if (c >= '0' && c <= '9')
                tmp = cpp_int(c - 48);
            else if (c >= 'a' && c <= 'f')
                tmp = cpp_int(c - 87);

            cpp_int tmp2 = powm(cpp_int(16), pre_res.length() - 1 - i, cpp_int(1) << 257);
            multiply(tmp, tmp, tmp2);
            add(res, res, tmp);
        }
        return res;
    }


    typedef struct PublicKeyRSA
    {
        cpp_int e;
        cpp_int n;

    } PKeyRSA;


    typedef struct SecretKeyRSA
    {
        PKeyRSA pkey;
        cpp_int p;
        cpp_int q;
        cpp_int d;

    } SKeyRSA;
};

#endif // __CRYPTO_UTILS_H
