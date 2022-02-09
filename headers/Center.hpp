#include <boost/multiprecision/cpp_int.hpp>

#include <BulletinBoard.hpp>


/**
 * @file Center.hpp
 * @brief Représente une autorité.
 */

using namespace boost::multiprecision;

class Center {

private:
    
    BulletinBoard board;
    std::pair<cpp_int, cpp_int> public_key;
    std::pair<cpp_int, cpp_int> private_key;

public:
    /**
     * @brief Get the board object
     * 
     * @return BulletinBoard 
     */
    BulletinBoard get_board();
    
    std::pair<cpp_int, cpp_int> get_public_key();
    std::pair<cpp_int, cpp_int> get_secret_key(); 

    /**
     * @brief Vérifie la justesse du vote sur le board d'une autorité.
     * 
     * @return true si le vote est juste
     * @return false si non
     */
    bool check_vote();

    /**
     * @brief Transmets le résultat du décompte d'une autorité à sa supérieure hiérarchique.
     * Publie le résultat du vote dans le cas de l'autorité nationale.
     */
    void transmit_results();

};

