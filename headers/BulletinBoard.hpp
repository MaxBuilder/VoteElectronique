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
    /**
     * @brief Vecteur des bulletins qui constituent le tableau
     */
    std::vector<Bulletin> board;

    /**
     * @brief Vecteur des résultats du décompte des lignes
     */
    std::vector<cpp_int> sums;

    /**
     * @brief Objet Verifier pour la vérification des votes
     */
    // Verifier verifier;

public:
    
    // Constructeur par défaut
    BulletinBoard() {};

    /**
     * @brief Get the board object
     * 
     * @return std::vector<Bulletin> 
     */
    std::vector<Bulletin> get_board() { return board; };

    /**
     * @brief Get the sums object
     * 
     * @return std::vector<cpp_int> 
     */
    std::vector<cpp_int> get_sums() { return sums; };

    /**
     * @brief Fait appel au Verifier pour vérifier que les votes sont corrects.
     * 
     * @return true 
     * @return false 
     */
    bool verify();

    /**
     * @brief Effectue le décompte des votes du `board` et l'écrit dans `sums`.
     * 
     */
    void make_tally();
};

#endif // __BULLETIN_BOARD_H__