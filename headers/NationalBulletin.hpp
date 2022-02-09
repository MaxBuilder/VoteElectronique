
#include <Bulletin.hpp>


class RegionalBulletin : public Bulletin {
private:
    cpp_int reg_sum;
    cpp_int nat_product;

public:
    cpp_int get_reg_sum();
    cpp_int get_nat_product();
};
