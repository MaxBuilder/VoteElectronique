#ifndef __NATIONAL_BULLETIN_H__
#define __NATIONAL_BULLETIN_H__

#include "Bulletin.hpp"


class NationalBulletin : public Bulletin {
private:
    cpp_int reg_sum;
    cpp_int nat_product;

public:
    NationalBulletin(cpp_int pseudo, cpp_int a, cpp_int b) : Bulletin(pseudo), reg_sum(a), nat_product(b) {};

    cpp_int get_reg_sum() { return reg_sum; };
    cpp_int get_nat_product() { return nat_product; };

    virtual void cout_board() {
        std::cout << "| " <<std::setfill(' ') << std::setw(5) << get_pseudonym() << " | " << std::setfill(' ') 
        << std::setw(5) << reg_sum << " | " << std::setfill(' ') << std::setw(5) << nat_product << " | " 
        << "     " << " |\n";
    }

    virtual ~NationalBulletin() {};
};

#endif // __NATIONAL_BULLETIN_H__