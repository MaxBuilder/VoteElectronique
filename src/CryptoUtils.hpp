#ifndef __CRYPTO_UTILS_H
#define __CRYPTO_UTILS_H

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>
#include "Encryption.hpp"
#include <vector>

using namespace boost::multiprecision;

typedef struct PublicKey
{
    cpp_int g;
    cpp_int N;
    cpp_int tetha;
    cpp_int beta;
    cpp_int m;
} PKey;

typedef struct CipherStruct
{
    cpp_int x;
    cpp_int cipher;
} CipherStruct;


typedef struct EqualityProof
{
    std::array<cpp_int, 3> u_j;
    cpp_int z;
    std::array<cpp_int, 3> v_j;
    cpp_int e; // Challenge donné par le vérificateur
} EqProof;

class CryptoUtils {
public:

    /**
     * @brief Renvoie un cpp_int aléatoire dans Z/NZ*
     * 
     * @return cpp_int un cpp_int aléatoire dans Z/NZ*.
     */
    static cpp_int getRandomZnZ(PKey PK) {

        boost::random::mt19937 mt;
        boost::random::uniform_int_distribution<cpp_int> ui(cpp_int(1), cpp_int(PK.N - 1));

        cpp_int res = 0;
        do {
            res = ui(mt);
        } while (res == 0);

        return res;
    }

    static EqProof generate_equality_proof(cpp_int m, std::array<CipherStruct, 3> ciphers, std::array<PublicKey, 3> pkeys, cpp_int e) {
        cpp_int ro = 0; // ToDo: ro = rand [0, 2^k[

        std::vector<cpp_int> s_j;
        EqProof res;
        res.e = e;
        CipherStruct cipher_res; 

        // On chiffre ro avec chacune des PK 
        for (size_t i = 0; i < 3; i++)  {
            cipher_res = Encryption::encrypt(pkeys[i], ro); 
            s_j[i] = cipher_res.x;
            res.u_j[i] = cipher_res.cipher;
        }

        // Calcul de Z 
        boost::multiprecision::multiply(m, m, e); // m*e
        res.z = ro + m; // z = ro + m*e 

        for (size_t i = 0; i < 3; i++)  {
            // r_je = r_j^e mod N_j
            cpp_int r_je = boost::multiprecision::powm(ciphers[i].x, e, pkeys[i].N);
            // res = s_j * r_j^e
            boost::multiprecision::multiply(res.v_j[i], s_j[i], r_je);
            // res = res mod N_j
            res.v_j[i] = boost::multiprecision::powm(res.v_j[i], 1, pkeys[i].N);
        }

        return res;
    }

};

#endif // __CRYPTO_UTILS_H
