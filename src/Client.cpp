#include "Client.hpp"

CryptoUtils::SKeyRSA Client::generateKeys()
{
    boost::random_device rn1;
    boost::random_device rn2;
    boost::random_device rn3;

    boost::random::mt11213b base_gen(rn1);
    boost::random::independent_bits_engine<boost::random::mt11213b, BITSIZE, cpp_int> gen(base_gen);

    boost::random::mt19937 gen2(rn2);

    cpp_int p;
    while (true)
    {
        p = gen();
        if (powm(p, 1, 2) == 0)
            continue;
        if (miller_rabin_test(p, 25, gen2))
            break;
    }

    cpp_int q;
    while (true)
    {
        q = gen();
        if (powm(q, 1, 2) == 0 || q == p)
            continue;
        if (miller_rabin_test(q, 25, gen2))
            break;
    }

    cpp_int N;
    multiply(N, p, q);

    cpp_int phi_N, e;
    multiply(phi_N, cpp_int(p - 1), cpp_int(q - 1));

    e = CryptoUtils::getRandomInversibleElement(phi_N);

    cpp_int d = boost::integer::mod_inverse(e, phi_N);
    CryptoUtils::SKeyRSA sk;
    sk.pkey.e = e;
    sk.pkey.n = N;
    sk.d = d;
    sk.p = p;
    sk.q = q;

    return sk;
}

cpp_int Client::signRSA(cpp_int message, CryptoUtils::SKeyRSA sk)
{
    cpp_int sign;

    cpp_int hash = CryptoUtils::sha256(boost::to_string(message));
    sign = powm(hash, sk.d, sk.pkey.n);
    return sign;
}

void Client::vote(int vote)
{
    cpp_int M_pow_vote = boost::multiprecision::pow(M, vote);

    // R�cup�ration des cl�s publiques des autorit�s locales, r�gionales et nationales
    std::array<PublicKey, 3> pkeys = loc->get_public_keys();

    // Cr�ation du vote local
    CipherStruct locVote = Encryption::encrypt(pkeys[0], M_pow_vote);
    cpp_int locSign = signRSA(locVote.cipher, sk);
    std::tuple<cpp_int, cpp_int, cpp_int> localVote = {locVote.cipher, locSign, cpp_int(0)}; // ToDo : La troisi�me preuve

    // Cr�ation du vote r�gional
    CipherStruct regVote = Encryption::encrypt(pkeys[1], M_pow_vote);
    cpp_int regSign = signRSA(regVote.cipher, sk);
    std::tuple<cpp_int, cpp_int, cpp_int> regionalVote = {regVote.cipher, regSign, cpp_int(0)};

    // Cr�ation du vote national
    CipherStruct natVote = Encryption::encrypt(pkeys[2], M_pow_vote);
    cpp_int natSign = signRSA(natVote.cipher, sk);
    std::tuple<cpp_int, cpp_int, cpp_int> nationalVote = {natVote.cipher, natSign, cpp_int(0)};

    // Génération de la preuve d'égalité des votes (zero-knowledge proof 3)
    EqProof eq_proof = Prover::generate_equality_proof(M_pow_vote, std::array<CipherStruct, 3>{locVote, regVote, natVote}, pkeys, Verifier::get_challenge());

    // Ajout du bulletin au BulletinBoard
    loc->get_bulletin_board().get_board().push_back(new LocalBulletin(client_id, sk.pkey, time(nullptr), localVote, regionalVote, nationalVote, eq_proof));
}