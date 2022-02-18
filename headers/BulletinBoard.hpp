#ifndef __BULLETIN_BOARD_H__
#define __BULLETIN_BOARD_H__

#include <vector>
#include "Bulletin.hpp"
// #include <Verifier.hpp>

/**
 * @class BulletinBoard
 * @brief Représente le tableau des bulletins de votes d'une autorité. 
 * 
 * @public `std::vector` Vecteur des bulletins qui constituent le tableau
 * @public `std::vector` Vecteur des résultats du décompte des lignes
 * @public `Verifier`    Objet Verifier pour la vérification des votes 
 */
class BulletinBoard {

private:
    // La liste des bulletins de vote.
    std::vector<Bulletin> board;

    // Décompte de chaque colonne
    std::vector<cpp_int> sums; 

    /**
     * @brief Objet Verifier pour la vérification des votes
     * // ToDo : réparer pour activer (ou passer en fonctions statiques (raph))
     */
    // Verifier verifier;

public:

    /**
     * @brief Retourne la référence du tableau des votes.
     * 
     * @return std::vector<Bulletin> & la référence du tableau des votes.
     */
    std::vector<Bulletin>& get_board();

    /**
     * @brief Retourne la référence du vecteur des décomptes.
     * 
     * @return std::vector<cpp_int> & la référence du vecteur des décomptes.
     */
    std::vector<cpp_int>& get_sums();

    /**
     * @brief Fait appel au Verifier pour filtrer les votes non-valables.
     * 
     * @return true si des votes incorrects ont été filtrés.
     * @return false sinon.
     */
    bool verify();


    /**
    * @brief Affiche le BulletinBoard.
    */
    void cout_board();
};

#endif // __BULLETIN_BOARD_H__