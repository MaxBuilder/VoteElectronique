#include "../headers/NationalAuthority.hpp"
#include "../headers/NationalBulletin.hpp"


std::vector<cpp_int> NationalAuthority::calculate_results(cpp_int M, int p) {
    
    cpp_int final_tally = get_bulletin_board().get_sums().at(0);
    std::vector<cpp_int> res;

    for (int i = 0; i < p; i++) {
        cpp_int q;
        cpp_int r;
        boost::multiprecision::divide_qr(final_tally, M, q, r);
        final_tally = q;
        boost::multiprecision::subtract(final_tally, final_tally, r);
        res.push_back(r);
    }

    return res;
}


void NationalAuthority::transmit_results() {
    // ToDo
}


void NationalAuthority::cout_board() {
    std::cout << "Board de l'autorité nationale :\n";
    get_bulletin_board().cout_board();

    std::cout << "| Sums. | ";
	for (size_t i = 0; i < get_bulletin_board().get_sums().size(); i++)  {
		std::cout << std::setfill(' ') << std::setw(5) << get_bulletin_board().get_sums()[i] << " | ";
	}
	std::cout << "\n";
}


void NationalAuthority::make_tally(cpp_int N) {

    cpp_int N2;
    boost::multiprecision::multiply(N2, N, N);

    cpp_int reg_sum = 0;
    cpp_int nat_prod = 1;

    for (Bulletin* b : get_bulletin_board().get_board()) {

        NationalBulletin * pt_b = (NationalBulletin *) b;

        cpp_int reg_vote = pt_b -> get_reg_sum();
        boost::multiprecision::add(reg_sum, reg_sum, reg_vote);
        reg_sum = boost::multiprecision::powm(reg_sum, 1, N2);

        cpp_int nat_vote = pt_b -> get_nat_product();
        boost::multiprecision::multiply(nat_prod, nat_prod, nat_vote);
        nat_prod = boost::multiprecision::powm(nat_prod, 1, N2);

    }

    //cpp_int decrypted_nat_prod = get_crypto().decrypt(nat_prod);

    get_bulletin_board().get_sums().push_back(reg_sum);
    //get_bulletin_board().get_sums().push_back(decrypted_nat_prod);
}
