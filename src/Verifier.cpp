#include "Verifier.hpp"

cpp_int Verifier::get_challenge() {
    // ToDo: générer challenge
    return cpp_int(0);
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
    for (size_t i = 0; i < board.size(); i++) {
        lb = (LocalBulletin*) board[i];
        proof = lb->get_equ_proof();
        
        // ToDo: Check si proof.z appartient à [0, 2^k]
       
        // ToDo: Calculer 3 termes gauche: pkeys[i].g^proof.z * proof.v_j[i]^pkeys[i].N
        // ToDo: Calculer terme droit pour chaque vote: 
            // proof.u_j[0] * lb->get_loc_vote()^proof.e
            // proof.u_j[1] * lb->get_reg_vote()^proof.e
            // proof.u_j[2] * lb->get_nat_vote()^proof.e
        // ToDo: Check égalité entre les termes gauches et droit
    }

    return fraud;
}