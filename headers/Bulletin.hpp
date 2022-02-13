#ifndef __BULLETIN_H__
#define __BULLETIN_H__


#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class Bulletin {

    private: 
        cpp_int pseudonym;

    public:
        Bulletin(cpp_int pseudo) : pseudonym(pseudo) {};


        cpp_int get_pseudonym() { return pseudonym; };

        virtual void cout_board() { std::cout << "non initialized board\n"; };

        virtual ~Bulletin() {}; 
    };

#endif // __BULLETIN_H__
