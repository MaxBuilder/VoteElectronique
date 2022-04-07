#include "Verifier.hpp"

cpp_int Verifier::get_challenge() {
    // ToDo: générer challenge de preuve entre [0, A[
    return cpp_int(323265);
}

bool Verifier::check_timestamp(std::vector<Bulletin*>& board) {
    bool fraud = false;

    // Lit le timestamp de fin de vote dans le fichier de configuration
    Properties *prop = Properties::getProperties();
    std::time_t end_time = prop->getVoteEnd();
    
    // Parcours des bulletins du board
    LocalBulletin *lb;
    for (size_t i = 0; i < board.size(); i++) {
        lb = (LocalBulletin*) board[i];
        if (lb->get_timestamp() > end_time) {
            // Suppression du vote frauduleux
            lb->set_validity(1);

            std::cout << "Vote frauduleux supprimé: ";
            lb->cout_board();
            fraud = true;
        }
	}
    
    return fraud;
}

bool Verifier::check_equality_proof(std::vector<Bulletin*>& board, std::array<PublicKey, 3> pkeys) {
    bool fraud = false;

    // Parcours des bulletins du board
    LocalBulletin *lb;
    EqProof proof;

    std::vector<cpp_int> gauche;
    std::vector<cpp_int> droit;

    cpp_int N2;
    cpp_int tmp;
    std::vector<cpp_int> ciphers;
    for (size_t i = 0; i < board.size(); i++) {
        lb = (LocalBulletin*) board[i];
        proof = lb->get_equ_proof();

        // Récupération des 3 votes chiffrés du bulletin
        ciphers.push_back( std::get<0>( lb->get_loc_vote() ) );
        ciphers.push_back( std::get<0>( lb->get_reg_vote() ) );
        ciphers.push_back( std::get<0>( lb->get_nat_vote() ) );
        
        // ToDo: Check si proof.z appartient à [0, 2^k]
        
        for (size_t i = 0; i < 3; i++)  {
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
            if (gauche[i] != droit[i]) {
                lb->set_validity(4);
                std::cout << "Vote frauduleux supprimé: ";
                lb->cout_board();
                fraud = true;
            }
        }
        gauche.clear();
        droit.clear();
        ciphers.clear();
    }

    return fraud;
}