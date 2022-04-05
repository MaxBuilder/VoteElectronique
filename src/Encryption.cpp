#include "Encryption.hpp"

cpp_int Encryption::encrypt(PKey PK, cpp_int M) {

    cpp_int N2 = boost::multiprecision::multiply(N2, PK.N, PK.N);
    cpp_int x = CryptoUtils::getRandomZnZ(PK);
    cpp_int chiffre;
    
    
    cpp_int term1 = boost::multiprecision::powm(PK.g, M, N2);
    cpp_int term2 = boost::multiprecision::powm(x, PK.N, N2);
    boost::multiprecision::multiply(chiffre, term1, term2);
    chiffre = boost::multiprecision::powm(chiffre, 1, N2);

    return chiffre;
}