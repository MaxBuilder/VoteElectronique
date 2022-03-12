#include "../headers/Verifier.hpp"


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
            std::cout << "Vote frauduleux supprimé: ";
            lb->cout_board();
            fraud = true;
            
            // Suppresion du vote frauduleux
            board.erase(board.begin()+i);
        }
	}
    
    return fraud;
};