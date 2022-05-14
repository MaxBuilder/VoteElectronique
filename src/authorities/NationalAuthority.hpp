#ifndef __NATIONAL_AUTHORITY_H__
#define __NATIONAL_AUTHORITY_H__

#include "Center.hpp"
#include "../bulletins/NationalBulletin.hpp"

/**
 * @brief Représente le centre national d'autorité.
 */
class NationalAuthority : public Center
{

public:
    // Constructeur
    NationalAuthority() : Center() {}

    /**
     * @brief Annonce les résultats de l'élection.
     */
    void transmit_results() override;

    /**
     * @brief Affiche le BulletinBoard d'une autorité sur la sortie standard.
     */
    void cout_board() override;

    /**
    * @brief Effectue le décompte des votes. 
    * Suppose que les votes sont déjà triés : on a supprimé ceux qui étaient invalides.
    *  
    * @return true si le résultat obtenu après déchiffrement est égal à la somme des résultats reçus par l'autorité inférieure
    * @return false si non
    */
    bool make_tally() override;

    /**
     * @brief Calcule et renvoie le vecteur du nombre de votes pour chaque candidat.
     */
    std::vector<cpp_int> calculate_results(cpp_int M, int p, cpp_int N);
};

#endif // __NATIONAL_AUTHORITY_H__
