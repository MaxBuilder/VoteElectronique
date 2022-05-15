#include "KeyGeneration.hpp"

/*
 * Return value tuple <>
 *  PKey : public key struct (N,g,thetha)
 *  cpp_int : Secret key m = m*beta.
 */
std::tuple<PKey, mp::cpp_int> KeyGeneration::generate_keys(bool verbose)
{
    Properties *prop = Properties::getProperties();
    int size_key = prop->get_keySize();
    boost::random_device rn;
    boost::random::mt19937 eng(rn());

    mp::cpp_int lw_bnd = mp::pow(cpp_int(2), size_key / 2);         // Lower bound for uniform int distribution = 2^512
    mp::cpp_int up_bnd = mp::pow(cpp_int(2), size_key / 2 + 1) - 1; // Upper Bound = 2^513 - 1

    boost::random::uniform_int_distribution<mp::cpp_int> prime_gen(lw_bnd, up_bnd);

    // For p,q = x defined bits (512, 256, 1024) => independent_bits_engine

    mp::cpp_int p, q, N, phiN, p_1, q_1, gcd;

    p = prime_gen(eng);
    while (!CryptoUtils::isSafePrime(p))
        p = prime_gen(eng);

    gcd = 0;
    while (gcd != 1)
    {
        while (!CryptoUtils::isSafePrime(q) || q == p)
        {
            q = prime_gen(eng);
        }

        mp::multiply(N, p, q);
        mp::subtract(p_1, p, cpp_int(1));
        mp::subtract(q_1, q, cpp_int(1));
        mp::multiply(phiN, p_1, q_1);
        gcd = mp::gcd(N, phiN); // N et phi(N) doivent être premiers entre eux 
    }

    mp::cpp_int Ntwo = mp::pow(N, 2);
    
    /* m = p'*q' where p = 2p' + 1 => p' = (p-1)/2
     *                 q = 2q' + 1 (see safe prime numbers)
     * p,q,p',q' are (different) prime numbers.
     *
     * >> 1 == divide by 2
     */
    mp::cpp_int m = ((p - 1) >> 1) * ((q - 1) >> 1);

    // Random generation part : beta, (a,b). ]0;N[

    // Must ensure that these 3 values are inversible in N for theta to be inversible
    mp::cpp_int beta = CryptoUtils::getRandomInversibleElement(N);
    mp::cpp_int a = CryptoUtils::getRandomInversibleElement(N);
    mp::cpp_int b = CryptoUtils::getRandomInversibleElement(N);

    // mp::cpp_int g = mp::powm(mp::powm(one + N, a, Ntwo) * mp::powm(b, N, Ntwo), 1, Ntwo);
    mp::cpp_int tmp1 = mp::powm(1 + N, a, Ntwo);
    mp::cpp_int tmp2 = mp::powm(b, N, Ntwo);
    mp::cpp_int g = mp::powm(tmp1 * tmp2, 1, Ntwo);

    mp::cpp_int tetha = powm(a * m * beta, 1, N);

    // PublicKey result
    PKey return_value{g, N, tetha, beta, m};

    // SecretKey result
    mp::cpp_int Skey = beta * m;

    /*
    std::cout << "Test de la génération de clé:\n"
              << "p: " << p << " | q: " << q << " | N: " << N << " | N^2 = " << Ntwo << "\n"
              << "m = p'*q' = " << m << "\n"
              << "Beta: " << beta << " | " << "a: " << a << " | b: " << b << "\n"
              << "g = (1+N)^a * b^N mod N^2 = " << g << "\n\n"
              << " > SK = beta*m = " << Skey << "\n"
              << "tetha = a*m*beta mod N = " << tetha << "\n"
              << " > PK = {g, N, tetha} = {" << g << ", " << N << ", " << tetha << "}\n\n";
    */
    if (verbose) {
        std::cout << "	Clé d'autorité générée | N : " << std::hex << std::uppercase << N << std::dec << "\n";
    }
    return std::make_tuple(return_value, Skey);
}