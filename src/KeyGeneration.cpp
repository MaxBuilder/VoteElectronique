#include "../headers/KeyGeneration.hpp"

using namespace boost;

/*
 * Return value tuple <>
 *  PKey : public key struct (N,g,thetha)
 *  cpp_int : Secret key m = m*beta.
 */
std::tuple<PKey, cpp_int> KeyGeneration()
{
    // Temporary example of 2 valid safe prime numbers.
    // ToDo safe prime test and prime generation.
    // For p,q = x defined bits (512, 256, 1024) => independent_bits_engine
    cpp_int p = 5;
    cpp_int q = 7;
    cpp_int N = p * q;
    cpp_int Ntwo = pow(N, 2);

    /* m = p'*q' where p = 2p' + 1 => p' = (p-1)/2
     *                 q = 2q' + 1 (see safe prime numbers)
     * p,q,p',q' are (different) prime numbers.
     *
     * >> 1 == divide by 2
     */
    cpp_int m = ((p - 1) >> 1) * ((q - 1) >> 1);

    // cpp_int sizeN = msb(N);
    // const cpp_int cstsize = sizeN;
    // typedef independent_bits_engine<mt19937, 10, cpp_int> ex;

    // Random generation part : beta, (a,b). ]0;N[
    cpp_int one = 1;
    random::mt19937 eng(clock());
    random::uniform_int_distribution<cpp_int> one_to_N(one, N - 1);

    cpp_int beta = one_to_N(eng);
    cpp_int a = one_to_N(eng);
    cpp_int b = one_to_N(eng);
    cpp_int g = powm(powm(one + N, a, Ntwo) * powm(b, N, Ntwo),
                     1,
                     Ntwo);

    cpp_int tetha = powm(a * m * beta, 1, N);

    // PublicKey result
    PKey return_value{g, N, tetha};

    // SecretKey result
    cpp_int Skey = beta * m;

    return std::make_tuple(return_value, Skey);
}