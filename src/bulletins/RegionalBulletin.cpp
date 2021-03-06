#include "RegionalBulletin.hpp"


cpp_int RegionalBulletin::get_loc_sum() { return loc_sum; }


cpp_int RegionalBulletin::get_reg_product() { return reg_product; }


cpp_int RegionalBulletin::get_nat_product() { return nat_product; }


void RegionalBulletin::cout_board() {
    std::cout << "	| " << std::hex 
    << std::setfill(' ') << std::setw(5) << get_pseudonym() << " | " 
    << std::setfill(' ') << std::setw(15) << loc_sum << " | " 
    << std::setfill(' ') << std::setw(15) << reg_product << " | " 
    << std::setfill(' ') << std::setw(15) << nat_product << " |\n" << std::dec;
}