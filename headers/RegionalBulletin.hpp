#ifndef __REGIONAL_BULLETIN_H__
#define __REGIONAL_BULLETIN_H__

#include "Bulletin.hpp"


class RegionalBulletin : public Bulletin {
private:
    cpp_int loc_sum;
    cpp_int reg_product;
    cpp_int nat_product;

public:
    RegionalBulletin(cpp_int pseudo, cpp_int a, cpp_int b, cpp_int c) : Bulletin(pseudo), loc_sum(a), reg_product(b), nat_product(c) {}
    
    cpp_int get_loc_sum() { return loc_sum; };
    cpp_int get_reg_product() { return reg_product; };
    cpp_int get_nat_product() { return nat_product; };

    virtual void cout_board() {
        std::cout << "| " <<std::setfill(' ') << std::setw(5) << get_pseudonym() << " | " << std::setfill(' ') 
        << std::setw(5) << loc_sum << " | " << std::setfill(' ') << std::setw(5) << reg_product << " | " 
        << std::setfill(' ') << std::setw(5) << nat_product << " |\n";
    }

    virtual ~RegionalBulletin() {};
};

#endif // __REGIONAL_BULLETIN_H__
