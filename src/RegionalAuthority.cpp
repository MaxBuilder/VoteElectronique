#include "../headers/RegionalAuthority.hpp"
#include "../headers/NationalBulletin.hpp"
#include "../headers/RegionalBulletin.hpp"


int RegionalAuthority::get_id() { return id; }


NationalAuthority& RegionalAuthority::get_sup_auth() { return national_auth; }


void RegionalAuthority::transmit_results() {
    
    // std::vector<Bulletin *> national_board = get_sup_auth().get_bulletin_board().get_board();

    int id = get_id();
    cpp_int reg_sum = get_bulletin_board().get_sums()[0];
    cpp_int nat_prod = get_bulletin_board().get_sums()[1];

    // NationalBulletin votes(id, reg_sum, nat_prod);

    // national_board.push_back(&votes);
    get_sup_auth().get_bulletin_board().get_board().push_back(
        new NationalBulletin(id, reg_sum, nat_prod) );
}


void RegionalAuthority::cout_board() {
    std::cout << "\033[;33mBoard de l'autorité régionale n°" << get_id() << " :\033[00m\n";
    get_bulletin_board().cout_board();

    std::cout << "| Sums. | ";
	for (size_t i = 0; i < get_bulletin_board().get_sums().size(); i++)  {
		std::cout << std::setfill(' ') << std::setw(5) << get_bulletin_board().get_sums()[i] << " | ";
	}
	std::cout << "\n";
}


void RegionalAuthority::make_tally(cpp_int N)
{
    cpp_int N2; // Le modulo auquel on fait les calculs de chiffrement
    boost::multiprecision::multiply(N2, N, N);

    // D�finition des variables contenant les produits des colonnes.
    cpp_int loc_sum = 0;
    cpp_int reg_prod = 1;
    cpp_int nat_prod = 1;

    for (Bulletin * b : get_bulletin_board().get_board()) {

        RegionalBulletin * pt_b = (RegionalBulletin *) b;

        cpp_int loc_vote = pt_b -> get_loc_sum();
        boost::multiprecision::add(loc_sum, loc_sum, loc_vote);
        loc_sum = boost::multiprecision::powm(loc_sum, 1, N2);

        cpp_int reg_vote = pt_b -> get_reg_product();
        boost::multiprecision::multiply(reg_prod, reg_vote, reg_prod);
        reg_prod = boost::multiprecision::powm(reg_prod, 1, N2);

        cpp_int nat_vote = pt_b -> get_nat_product();
        boost::multiprecision::multiply(nat_prod, nat_vote, nat_prod);
        nat_prod = boost::multiprecision::powm(nat_prod, 1, N2);

    }

    //cpp_int decrypted_reg_prod = get_crypto().decrypt(reg_prod);		// Une fois la classe CryptoManager cr��e

    get_bulletin_board().get_sums().push_back(loc_sum);
    //get_bulletin_board().get_sums().push_back(decrypted_reg_prod);
    get_bulletin_board().get_sums().push_back(-1); // temporaire pour l'affichage du board
    get_bulletin_board().get_sums().push_back(nat_prod);
}
