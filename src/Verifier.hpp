#ifndef __VERIFIER_H__
#define __VERIFIER_H__

#include "Properties.hpp"
#include "Prover.hpp"
#include "authorities/BulletinBoard.hpp"
#include "bulletins/LocalBulletin.hpp"
#include <ctime>

class Verifier {

public:

    /**
     * @brief Renvoie un challenge au Prover pour les preuves zero-knowledge
     * 
     * @return cpp_int appartenant à l'ensemble [0, A[
     */
    static cpp_int get_challenge();

    /**
     * @brief L'autorité locale s'assure qu'un vote a été finalisé avant la date limite. 
     * 
     * @return true 
     * @return false 
     */
    static bool check_timestamp(std::vector<Bulletin*>& board);

    /**
     * @brief L'autorité vérifie la signature de chacun des votes.
     * 
     * @return true 
     * @return false 
     */
    static bool check_signature(std::vector<Bulletin*>& board);

    /**
     * @brief Vérifie la preuve que le chiffré est celui d'un vote correct (zero-knowledge proof 2).
     * 
     * @return true 
     * @return false 
     */
    static bool check_legal_vote(BulletinBoard);

    /**
     * @brief Vérifie la preuve que les 3 chiffrés correspondent au même clair (zero-knowledge proof 3).
     * 
     * @return true 
     * @return false 
     */
    static bool check_equality_proof(std::vector<Bulletin*>& board, std::array<PublicKey, 3> pkeys);

    /**
     * @brief Compare les résultats obtenus avec ceux fournis par les autorités inférieures.
     * 
     * @return true 
     * @return false 
     */
    static bool compare_results(BulletinBoard);

    static bool verifySignatureRSA(cpp_int message, cpp_int sign, CryptoUtils::PKeyRSA pk);
};

#endif // __VERIFIER_H__
