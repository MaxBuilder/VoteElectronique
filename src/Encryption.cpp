#include "Encryption.hpp"

CipherStruct Encryption::encrypt(PKey PK, cpp_int M) {

    cpp_int N2;
    boost::multiprecision::multiply(N2, PK.N, PK.N);
    std::vector<cpp_int> group = CryptoUtils::getInversibleGroup(PK.N);
    int group_order = group.size();
    
    boost::random_device rn;
    boost::random::mt19937 mt(rn);
    boost::random::uniform_int_distribution<cpp_int> ui(cpp_int(1), group_order - 1);

    cpp_int x = group[(int)ui(mt)];
    CipherStruct res;
    res.x = x;
    
    
    cpp_int term1 = boost::multiprecision::powm(PK.g, M, N2);
    cpp_int term2 = boost::multiprecision::powm(x, PK.N, N2);
    boost::multiprecision::multiply(res.cipher, term1, term2);
    res.cipher = boost::multiprecision::powm(res.cipher, 1, N2);

    return res;
}