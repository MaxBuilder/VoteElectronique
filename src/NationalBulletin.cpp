#include "../headers/NationalBulletin.hpp"

cpp_int NationalBulletin::get_reg_sum() { return reg_sum; }


cpp_int NationalBulletin::get_nat_product() { return nat_product; }


void NationalBulletin::cout_board() {
	std::cout << "National Bulletin: " << get_pseudonym() << "  |  " << reg_sum << "  |  " << nat_product << "  " << std::endl;
}

// void cout_board() {
// 	std::cout << "| " <<std::setfill(' ') << std::setw(5) << get_pseudonym() << " | " << std::setfill(' ') 
// 	<< std::setw(5) << reg_sum << " | " << std::setfill(' ') << std::setw(5) << nat_product << " | " 
// 	<< "     " << " |\n";
// }