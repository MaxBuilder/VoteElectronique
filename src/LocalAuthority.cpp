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
    // ToDo : moyen de bloquer l'écriture sur les autres lignes que la sienne
    // ToDo : pseudo des locales = id ? 
    get_regional_auth().receive_results(get_id(), get_bulletin_board().get_sums());
};

/**
 * @brief Affiche le BulletinBoard d'une autorité sur la sortie standard.
 */
void LocalAuthority::print_board() {
        if (get_bulletin_board().get_board().size() > 0) {
            std::cout << " > Local board: ("<< get_bulletin_board().get_board().size() << " entries)\n";
            for (size_t i = 0; i < get_bulletin_board().get_board().size(); i++)  {
                LocalBulletin *casted_bulletin = (LocalBulletin*) get_bulletin_board().get_board()[i];  
                casted_bulletin->cout_board();
            }
        }
        else {
            std::cout << " > Local board empty\n";
        }

        std::cout << "| Sums. | ";
        for (size_t i = 0; i < get_bulletin_board().get_sums().size(); i++)  {
            std::cout << std::setfill(' ') << std::setw(5) << get_bulletin_board().get_sums()[i] << " | ";
        }
        std::cout << "\n";
    }
