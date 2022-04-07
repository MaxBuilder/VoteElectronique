#include "Prover.hpp"

EqProof Prover::generate_equality_proof(cpp_int m, std::array<CipherStruct, 3> ciphers, std::array<PublicKey, 3> pkeys, cpp_int challenge) {
        // ro = rand [0, 2^k[
        boost::random::mt19937 eng(clock());
        boost::random::uniform_int_distribution<cpp_int> one_to_N(cpp_int(1), pkeys[0].N - 1);
        cpp_int ro = one_to_N(eng);

        std::vector<cpp_int> s_j;
        EqProof res;
        res.e = challenge;
        CipherStruct cipher_res;

        // On chiffre ro avec chacune des PK 
        for (size_t i = 0; i < 3; i++)  {
            cipher_res = Encryption::encrypt(pkeys[i], ro); 
            
            s_j.push_back(cipher_res.x); 
            res.u_j.push_back(cipher_res.cipher);
        }

        // Calcul de Z 
        boost::multiprecision::multiply(m, m, res.e); // m*e
        res.z = ro + m; // z = ro + m*e 

        for (size_t i = 0; i < 3; i++)  {
            // r_je = r_j^e mod N_j
            cpp_int r_je = boost::multiprecision::powm(ciphers[i].x, res.e, pkeys[i].N);
            // res = s_j * r_j^e
            res.v_j.push_back(cpp_int(0));
            boost::multiprecision::multiply(res.v_j[i], s_j[i], r_je);
            // res = res mod N_j
            res.v_j[i] = boost::multiprecision::powm(res.v_j[i], 1, pkeys[i].N);
        }

        return res;
    }