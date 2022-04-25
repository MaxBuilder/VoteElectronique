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

    std::vector<cpp_int> group = CryptoUtils::getInversibleGroup(phi_N);
    int group_order = group.size();
    boost::random::mt19937 mt(rn3);
    boost::random::uniform_int_distribution<int> ui(0, group_order - 1);
    e = group[ui(mt)];

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

    cpp_int hash = CryptoUtils::sha256(to_string(message));
    sign = powm(hash, sk.d, sk.pkey.n);
    return sign;
}


void Client::vote(int vote)
{
    // Création du message M
    cpp_int nbVoters = props->get_nbVoters();
    int bitsize = (int) boost::multiprecision::msb(nbVoters) + 1;
    cpp_int M = boost::multiprecision::pow(cpp_int(2), bitsize);
    M = boost::multiprecision::pow(M, vote);

    // Récupération des clés publiques des autorités locales, régionales et nationales
    std::array<PublicKey, 3> pkeys = loc -> get_public_keys();

    // Création du vote local
    CipherStruct locVote = Encryption::encrypt(pkeys[0], M);
    cpp_int locSign = signRSA(M, sk);
    std::tuple<cpp_int, cpp_int, cpp_int> localVote = { locVote.cipher, locSign, cpp_int(0) }; // ToDO : La troisième preuve

    // Création du vote régional
    CipherStruct regVote = Encryption::encrypt(pkeys[1], M);
    cpp_int regSign = signRSA(M, sk);
    std::tuple<cpp_int, cpp_int, cpp_int> regionalVote = { regVote.cipher, regSign, cpp_int(0) };

    // Création du vote national
    CipherStruct natVote = Encryption::encrypt(pkeys[2], M);
    cpp_int natSign = signRSA(M, sk);
    std::tuple<cpp_int, cpp_int, cpp_int> nationalVote = { natVote.cipher, natSign, cpp_int(0) };
    
    // La preuve d'égalité des chiffrés
    EqProof eq_proof = Prover::generate_equality_proof(vote, std::array<CipherStruct, 3> {locVote, regVote, natVote}, pkeys, Verifier::get_challenge());

    // Ajout du bulletin au BulletinBoard
    loc->get_bulletin_board().get_board().push_back(new LocalBulletin(client_id, sk.pkey, time(nullptr), localVote, regionalVote, nationalVote, eq_proof));
}