#include "KeyGeneration.hpp"

/*
 * Return value tuple <>
 *  PKey : public key struct (N,g,thetha)
 *  cpp_int : Secret key m = m*beta.
 */
std::tuple<PKey, mp::cpp_int> KeyGeneration::generate_keys()
{
    // Temporary example of 2 valid safe prime numbers.
    // ToDo safe prime test and prime generation.
    // For p,q = x defined bits (512, 256, 1024) => independent_bits_engine
    mp::cpp_int p = 5;
    mp::cpp_int q = 7;
    mp::cpp_int N = p * q;
    mp::cpp_int Ntwo = mp::pow(N, 2);

    // Le groupe Z/nZ* et son ordre
    std::vector<cpp_int> group = CryptoUtils::getInversibleGroup(N);
    int group_order = group.size();

    /* m = p'*q' where p = 2p' + 1 => p' = (p-1)/2
     *                 q = 2q' + 1 (see safe prime numbers)
     * p,q,p',q' are (different) prime numbers.
     *
     * >> 1 == divide by 2
     */
    mp::cpp_int m = ((p - 1) >> 1) * ((q - 1) >> 1);

    // cpp_int sizeN = msb(N);
    // const cpp_int cstsize = sizeN;
    // typedef independent_bits_engine<mt19937, 10, cpp_int> ex;

    // Random generation part : beta, (a,b). ]0;N[

    // Must ensure that these 3 values are inversible in N for theta to be inversible
    boost::random_device rn;
    boost::random::mt19937 mt(rn());
    boost::random::uniform_int_distribution<cpp_int> ui(cpp_int(0), group_order - 1);

    mp::cpp_int beta = group[(int) ui(mt)];
    mp::cpp_int a = group[(int)ui(mt)];
    mp::cpp_int b = group[(int)ui(mt)];

    // mp::cpp_int g = mp::powm(mp::powm(one + N, a, Ntwo) * mp::powm(b, N, Ntwo), 1, Ntwo);
    mp::cpp_int tmp1 = mp::powm(1 + N, a, Ntwo);
    mp::cpp_int tmp2 = mp::powm(b, N, Ntwo);
    mp::cpp_int g = mp::powm(tmp1 * tmp2, 1, Ntwo);

    mp::cpp_int tetha = powm(a * m * beta, 1, N);

    // PublicKey result
    PKey return_value{g, N, tetha, beta, m};

    // SecretKey result
    mp::cpp_int Skey = beta * m;

    
    std::cout << "Test de la génération de clé:\n"
              << "p: " << p << " | q: " << q << " | N: " << N << " | N^2 = " << Ntwo << "\n"
              << "m = p'*q' = " << m << "\n"
              << "Beta: " << beta << " | " << "a: " << a << " | b: " << b << "\n"
              << "g = (1+N)^a * b^N mod N^2 = " << g << "\n\n"
              << " > SK = beta*m = " << Skey << "\n"
              << "tetha = a*m*beta mod N = " << tetha << "\n"
              << " > PK = {g, N, tetha} = {" << g << ", " << N << ", " << tetha << "}\n\n";

    return std::make_tuple(return_value, Skey);
}