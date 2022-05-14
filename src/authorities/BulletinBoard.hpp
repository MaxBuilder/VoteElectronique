#ifndef __BULLETIN_BOARD_H__
#define __BULLETIN_BOARD_H__

#include <vector>
#include "../bulletins/Bulletin.hpp"

/**
 * @class BulletinBoard
 * @brief Représente le tableau des bulletins de votes d'une autorité.
 *
 * @public `std::vector` Vecteur des bulletins qui constituent le tableau
 * @public `std::vector` Vecteur des résultats du décompte des lignes
 * @public `Verifier`    Objet Verifier pour la vérification des votes
 */
class BulletinBoard
{

private:
    std::vector<Bulletin *> board; // La liste des bulletins de vote.

    std::vector<cpp_int> sums; // Décompte de chaque colonne

public:
    /**
     * @brief Retourne la référence du tableau des votes.
     *
     * @return std::vector<Bulletin *> & la référence du tableau des votes.
     */
    std::vector<Bulletin *> &get_board();

    /**
     * @brief Retourne une copie du board.
     *
     * @return std::vector<Bulletin *> une copie du board.
     */
    std::vector<Bulletin *> get_board_copy();

    /**
     * @brief Retourne la référence du vecteur des décomptes.
     *
     * @return std::vector<cpp_int> & la référence du vecteur des décomptes.
     */
    std::vector<cpp_int> &get_sums();

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