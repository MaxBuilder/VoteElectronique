#include <tuple>

#include "LocalAuthority.hpp"

int LocalAuthority::get_id() { return id; }

RegionalAuthority &LocalAuthority::get_sup_auth() { return regional_auth; }

std::array<PublicKey, 3> LocalAuthority::get_public_keys()
{
	PublicKey p1 = get_public_key();
	PublicKey p2 = get_sup_auth().get_public_key();
	PublicKey p3 = get_sup_auth().get_sup_auth().get_public_key();

	std::array<PublicKey, 3> res{p1, p2, p3};
	return res;
}

void LocalAuthority::transmit_results()
{
	int id = get_id();
	cpp_int loc_sum = get_bulletin_board().get_sums()[0];
	cpp_int reg_prod = get_bulletin_board().get_sums()[1];
	cpp_int nat_prod = get_bulletin_board().get_sums()[2];

	get_sup_auth().get_bulletin_board().get_board().push_back(
		new RegionalBulletin(id, loc_sum, reg_prod, nat_prod));
}

void LocalAuthority::cout_board()
{
	std::cout << "	\033[;34mBoard de l'autorité locale n°[" << get_sup_auth().get_id() << "," << get_id() << "] :\033[0m\n";
	std::cout << "	\033[1m| Timesta. | Sig |   Local vote    |  Regional vote  |  National vote  | Validity\n\033[0m";
	get_bulletin_board().cout_board();
 
	std::cout << "	\033[1m            Sums | ";
	for (size_t i = 0; i < get_bulletin_board().get_sums().size(); i++)
	{
		std::cout << std::setfill(' ') << std::setw(15) << std::hex 
		<< get_bulletin_board().get_sums()[i] 
		<< " | " << std::dec;
	}
	std::cout << "\033[0m\n\n";
}

bool LocalAuthority::make_tally()
{
	cpp_int N = get_public_key().N;
	cpp_int loc_N2, reg_N2, nat_N2; // Le modulo auquel on fait les calculs de chiffrement
	nat_N2 = get_sup_auth().get_sup_auth().get_public_key().N;
	reg_N2 = get_sup_auth().get_public_key().N;

	boost::multiprecision::multiply(loc_N2, N, N);
	boost::multiprecision::multiply(reg_N2, reg_N2, reg_N2);
	boost::multiprecision::multiply(nat_N2, nat_N2, nat_N2);

	// Définition des variables contenant les produits des colonnes.
	cpp_int loc_res = 1;
	cpp_int reg_res = 1;
	cpp_int nat_res = 1;

	for (Bulletin *b : get_bulletin_board().get_board_copy())
	{

		LocalBulletin *pt_b = (LocalBulletin *)b;

		if (pt_b->get_validity() != 0)
			continue;

		cpp_int loc_vote = std::get<0>(pt_b->get_loc_vote());
		boost::multiprecision::multiply(loc_res, loc_res, loc_vote);
		loc_res = boost::multiprecision::powm(loc_res, 1, loc_N2);

		cpp_int reg_vote = std::get<0>(pt_b->get_reg_vote());
		boost::multiprecision::multiply(reg_res, reg_res, reg_vote);
		reg_res = boost::multiprecision::powm(reg_res, 1, reg_N2);

		cpp_int nat_vote = std::get<0>(pt_b->get_nat_vote());
		boost::multiprecision::multiply(nat_res, nat_res, nat_vote);
		nat_res = boost::multiprecision::powm(nat_res, 1, nat_N2);
	}

	// Déchiffrement de la somme locale
	get_combiner().calculateResults(loc_res);
	get_bulletin_board().get_sums().push_back(get_combiner().combine());

	get_bulletin_board().get_sums().push_back(reg_res);
	get_bulletin_board().get_sums().push_back(nat_res);

	return true;
}