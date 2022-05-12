#ifndef __PROVER_H__
#define __PROVER_H__

#include "cryptosystem/Encryption.hpp"
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

typedef struct EqualityProof
{
    std::vector<cpp_int> u_j;
    cpp_int z;
    std::vector<cpp_int> v_j;
    cpp_int e; // Challenge donné par le vérificateur
} EqProof;

class Prover {

public:

    static EqProof generate_equality_proof(cpp_int m, std::array<CipherStruct, 3> ciphers, std::array<PublicKey, 3> pkeys, cpp_int challenge);

};

#endif 