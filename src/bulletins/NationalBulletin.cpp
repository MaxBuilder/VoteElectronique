#include "NationalBulletin.hpp"

cpp_int NationalBulletin::get_reg_sum() { return reg_sum; }


cpp_int NationalBulletin::get_nat_product() { return nat_product; }


void NationalBulletin::cout_board() {
	std::cout << "	| " << std::hex 
        << std::setfill(' ') << std::setw(5) << get_pseudonym() << " | "
        << std::setfill(' ') << std::setw(15) << reg_sum << " | " 
        << std::setfill(' ') << std::setw(15) << nat_product 
        << " |\n" << std::dec;
}