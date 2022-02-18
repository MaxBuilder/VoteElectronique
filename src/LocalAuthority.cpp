#include "../headers/LocalAuthority.hpp"
#include "../headers/RegionalBulletin.hpp"


int LocalAuthority::get_id() { return id; }


RegionalAuthority& LocalAuthority::get_sup_auth() { return regional_auth; }


std::array<PublicKey, 3> LocalAuthority::get_public_keys() {
	PublicKey p1 = get_public_key();
	PublicKey p2 = get_sup_auth().get_public_key();
	PublicKey p3 = get_sup_auth().get_sup_auth().get_public_key();

	std::array<PublicKey, 3> res {p1, p2, p3};
	return res;
}


void LocalAuthority::transmit_results() {

	std::vector<Bulletin> regional_board = get_sup_auth().get_bulletin_board().get_board();
	
	int id = get_id();
	cpp_int loc_sum = get_bulletin_board().get_sums()[0];
	cpp_int reg_prod = get_bulletin_board().get_sums()[1];
	cpp_int nat_prod = get_bulletin_board().get_sums()[2];
	
	RegionalBulletin votes(id, loc_sum, reg_prod, nat_prod);

	regional_board.push_back(votes);
}

/**
 * @brief Affiche le BulletinBoard d'une autorité sur la sortie standard.
 */
void LocalAuthority::cout_board() {
	std::cout << "Board de l'autorité locale n°" << get_id() << " : " << std::endl;
	get_bulletin_board().cout_board();
}

void LocalAuthority::make_tally() {
	// ToDo
}

// void LocalAuthority::cout_board() {
//         if (get_bulletin_board().get_board().size() > 0) {
//             std::cout << " > Local board: ("<< get_bulletin_board().get_board().size() << " entries)\n";
//             for (size_t i = 0; i < get_bulletin_board().get_board().size(); i++)  {
//                 LocalBulletin *casted_bulletin = (LocalBulletin*) get_bulletin_board().get_board()[i];  
//                 casted_bulletin->cout_board();
//             }
//         }
//         else {
//             std::cout << " > Local board empty\n";
//         }

//         std::cout << "| Sums. | ";
//         for (size_t i = 0; i < get_bulletin_board().get_sums().size(); i++)  {
//             std::cout << std::setfill(' ') << std::setw(5) << get_bulletin_board().get_sums()[i] << " | ";
//         }
//         std::cout << "\n";
//     }
