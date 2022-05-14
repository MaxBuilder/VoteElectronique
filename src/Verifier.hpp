#ifndef __VERIFIER_H__
#define __VERIFIER_H__

#include "Properties.hpp"
#include "Prover.hpp"
#include "authorities/BulletinBoard.hpp"
#include "bulletins/LocalBulletin.hpp"
#include <boost/exception/to_string.hpp>
#include <ctime>

namespace mp = boost::multiprecision;

class Verifier
{

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
     * @return int Nombre de bulletins frauduleux retirés
     */
    static int check_timestamp(LocalBulletin *lb, std::time_t end_time);

    static bool verifySignatureRSA(cpp_int message, cpp_int sign, CryptoUtils::PKeyRSA pk);

    /**
     * @brief L'autorité vérifie la signature de chacun des votes.
     *
     * @return int Nombre de bulletins frauduleux retirés
     */
    static int check_signature(LocalBulletin *lb);

    /**
     * @brief Vérifie la preuve que le chiffré est celui d'un vote correct (zero-knowledge proof 2).
     *
     * @return int Nombre de bulletins frauduleux retirés
     */
    static int check_legal_vote(LocalBulletin *lb);

    /**
     * @brief Vérifie la preuve que les 3 chiffrés correspondent au même clair (zero-knowledge proof 3).
     *
     * @return int Nombre de bulletins frauduleux retirés
     */
    static int check_equality_proof(LocalBulletin *lb, std::array<PublicKey, 3> pkeys);

    /**
     * @brief Parcours du board local et appel successif des vérifications de Timestamp, signature, preuve de vote et preuve d'égalité
     * 
     * @param board 
     * @return int Nombre de bulletins frauduleux retirés  
     */
    static int filter_local_board(std::vector<Bulletin*>& board, std::array<PublicKey, 3> pkeys); 
};

#endif // __VERIFIER_H__
