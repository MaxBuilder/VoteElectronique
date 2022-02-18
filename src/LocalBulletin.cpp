#include "../headers/LocalBulletin.hpp"



time_t LocalBulletin::get_timestamp() { return timestamp; }


std::tuple<cpp_int, cpp_int, cpp_int> LocalBulletin::get_loc_vote() { return loc_vote; }


std::tuple<cpp_int, cpp_int, cpp_int>  LocalBulletin::get_reg_vote() { return reg_vote; }


std::tuple<cpp_int, cpp_int, cpp_int> LocalBulletin::get_nat_vote() { return nat_vote; }


cpp_int LocalBulletin::get_equ_proof() { return equ_proof; }


void LocalBulletin::cout_board() {
	std::cout << " > LocalBulletin: " << get_pseudonym() << ", " << timestamp << ", " << std::get<0>(loc_vote) << std::endl;
}