#include "Verifier.hpp"

cpp_int Verifier::get_challenge()
{
    boost::random_device rn;
    boost::random::mt19937 eng(rn());
    mp::cpp_int lw_bnd = cpp_int(1);        // Lower bound = 1
    mp::cpp_int up_bnd = cpp_int((2 ^ 80)); // Upper Bound = 2^80
    boost::random::uniform_int_distribution<mp::cpp_int> challenge_gen(lw_bnd, up_bnd);

    return challenge_gen(eng);
}

int Verifier::check_timestamp(LocalBulletin *lb, std::time_t end_time) 
{
    int fraud = 0;
    
    if (lb->get_timestamp() > end_time) {
        lb->set_validity(1); // Suppression du vote frauduleux
        fraud  += 1;
	}

    return fraud;
}


bool Verifier::verifySignatureRSA(cpp_int message, cpp_int sign, CryptoUtils::PKeyRSA pk)
{
    cpp_int mustBe = CryptoUtils::sha256(boost::to_string(message));
    mustBe = powm(mustBe, 1, pk.n);

    cpp_int test = powm(sign, pk.e, pk.n);

    if (mustBe == test)
        return true;
    return false;
}


int Verifier::check_signature(LocalBulletin* lb)
{
    int fraud = 0;

    std::tuple<cpp_int, cpp_int, cpp_int> loc_vote = lb->get_loc_vote();
    std::tuple<cpp_int, cpp_int, cpp_int> reg_vote = lb->get_reg_vote();
    std::tuple<cpp_int, cpp_int, cpp_int> nat_vote = lb->get_nat_vote();
    CryptoUtils::PKeyRSA pk = lb->get_pkey_RSA();


    if (!verifySignatureRSA(std::get<0>(loc_vote), std::get<1>(loc_vote), pk) ||
        !verifySignatureRSA(std::get<0>(reg_vote), std::get<1>(reg_vote), pk) ||
        !verifySignatureRSA(std::get<0>(nat_vote), std::get<1>(nat_vote), pk))
    {
        lb->set_validity(2);
        fraud += 1;
    }

    return fraud;
}


int Verifier::check_equality_proof(LocalBulletin *lb, std::array<PublicKey, 3> pkeys)
{
    int fraud = 0;

    EqProof proof;

    std::vector<cpp_int> gauche;
    std::vector<cpp_int> droit;

    cpp_int N2;
    cpp_int tmp;
    std::vector<cpp_int> ciphers;
    

    proof = lb->get_equ_proof();

    // Récupération des 3 votes chiffrés du bulletin
    ciphers.push_back(std::get<0>(lb->get_loc_vote()));
    ciphers.push_back(std::get<0>(lb->get_reg_vote()));
    ciphers.push_back(std::get<0>(lb->get_nat_vote()));

    // ToDo: Check si proof.z appartient à [0, 2^k]

    for (size_t i = 0; i < 3; i++)
    {
        boost::multiprecision::multiply(N2, pkeys[i].N, pkeys[i].N);

        // Calcul des termes gauche: pkeys[i].g^proof.z * proof.v_j[i]^pkeys[i].N
        gauche.push_back(cpp_int(0));
        gauche[i] = boost::multiprecision::powm(pkeys[i].g, proof.z, N2);
        tmp = boost::multiprecision::powm(proof.v_j[i], pkeys[i].N, N2);
        boost::multiprecision::multiply(gauche[i], gauche[i], tmp);
        gauche[i] = boost::multiprecision::powm(gauche[i], 1, N2);

        // Calcul des termes droit: proof.u_j[0] * ciphers[i]^proof.e
        droit.push_back(cpp_int(0));
        droit[i] = boost::multiprecision::powm(ciphers[i], proof.e, N2);
        boost::multiprecision::multiply(droit[i], droit[i], proof.u_j[i]);
        droit[i] = boost::multiprecision::powm(droit[i], 1, N2);

        // Check égalité entre les termes gauches et droit
        if (gauche[i] != droit[i])
        {
            lb->set_validity(4);
            fraud += 1;
        }
    }
    gauche.clear();
    droit.clear();
    ciphers.clear();

    return fraud;
}


int Verifier::filter_local_board(std::vector<Bulletin*>& board, std::array<PublicKey, 3> pkeys)
{
    // Lit le timestamp de fin de vote dans le fichier de configuration
    Properties *prop = Properties::getProperties();
    std::time_t end_time = prop->getVoteEnd();

    int tmp_res;
    int total_fraud = 0;

    LocalBulletin* lb;
    // Parcours des bulletins du board en les castant en lbal bulletin
    for (size_t i = 0; i < board.size(); i++) {
        lb = (LocalBulletin*)board[i];
        // Filtrage des boards par timestamp
        tmp_res = check_timestamp(lb, end_time);
        total_fraud += tmp_res;
        if (tmp_res)    continue;

        // Filtrage des boards par signature de vote
        tmp_res = check_signature(lb);
        total_fraud += tmp_res;
        if (tmp_res)    continue;

        // ToDo: Filtrage des boards par preuve de vote
        // if (check_legal_vote(lb))            continue;

        // Filtrage des boards par preuve d'égalité des textes clairs
        tmp_res = check_equality_proof(lb, pkeys);
        total_fraud += tmp_res;
        if (tmp_res)    continue;
    }

    return total_fraud;
}