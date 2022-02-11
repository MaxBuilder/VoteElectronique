#include "../headers/LocalAuthority.hpp"


/**
* @brief Retourne les clés publiques de l'autorité locale et de ses deux autorités supérieures.
* 
* @return std::array<PublicKey, 3> 
*/
std::array<PublicKey, 3> LocalAuthority::get_public_keys() {
    std::array<PublicKey, 3> p_keys;
    
    p_keys[0] = get_public_key();
    p_keys[1] = get_regional_auth().get_public_key();
    p_keys[2] = get_regional_auth().get_national_auth().get_public_key();

    return p_keys;
};
        

/**
* @brief Transmets le résultat du décompte d'une autorité à sa supérieure hiérarchique.
* Publie le résultat du vote dans le cas de l'autorité nationale.
*/
void LocalAuthority::transmit_results() {
    // Récupère son tableau Sums
    // L'écrit dans sa ligne (son ID) sur le board de la régionale
    // get_regional_auth().get_board()
    return;
};

