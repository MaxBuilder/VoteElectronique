
#include <Bulletin.hpp>


class RegionalBulletin : public Bulletin {
private:
    cpp_int loc_sum;
    cpp_int reg_product;
    cpp_int nat_product;

public:
    cpp_int get_loc_sum();
    cpp_int get_reg_product();
    cpp_int get_nat_product();
};
