#include "Encryption.hpp"

CipherStruct Encryption::encrypt(PKey PK, cpp_int M) {

    cpp_int N2;
    boost::multiprecision::multiply(N2, PK.N, PK.N);

    cpp_int x = CryptoUtils::getRandomInversibleElement(PK.N);
    CipherStruct res;
    res.x = x;
    
    
    cpp_int term1 = boost::multiprecision::powm(PK.g, M, N2);
    cpp_int term2 = boost::multiprecision::powm(x, PK.N, N2);
    boost::multiprecision::multiply(res.cipher, term1, term2);
    res.cipher = boost::multiprecision::powm(res.cipher, 1, N2);

    return res;
}