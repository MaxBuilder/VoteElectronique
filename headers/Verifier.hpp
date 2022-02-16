#ifndef __VERIFIER_H__
#define __VERIFIER_H__

#include "BulletinBoard.hpp"

class Verifier {

// private:
//     BulletinBoard board;

public:

    // Verifier(BulletinBoard _board) : board(_board) {}

    /**
     * @brief L'autorité locale s'assure qu'un vote a été finalisé avant la date limite. 
     * 
     * @return true 
     * @return false 
     */
    static bool check_timestamp(BulletinBoard);

    /**
     * @brief L'autorité vérifie la signature de chacun des votes.
     * 
     * @return true 
     * @return false 
     */
    static bool check_signature(BulletinBoard);

    /**
     * @brief Vérifie que le vote d'un utilisateur est complet.
     * 
     * @return true 
     * @return false 
     */
    static bool check_complete_vote(BulletinBoard);

    /**
     * @brief Vérifie la preuve que le chiffré est celui d'un vote correct (zero-knowledge proof 1).
     * 
     * @return true 
     * @return false 
     */
    static bool check_legal_vote(BulletinBoard);

    /**
     * @brief Vérifie la preuve que les chiffrés correspondent au même clair (zero-knowledge proof 3).
     * 
     * @return true 
     * @return false 
     */
    static bool check_same_vote(BulletinBoard);

    /**
     * @brief Compare les résultats obtenus avec ceux fournis par les autorités inférieures.
     * 
     * @return true 
     * @return false 
     */
    static bool compare_results(BulletinBoard);

    // ~Verifier();
};

#endif // __VERIFIER_H__
