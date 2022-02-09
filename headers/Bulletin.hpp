#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class Bulletin {

private: 
    cpp_int pseudonym;
public:
    cpp_int get_pseudonym();
};
