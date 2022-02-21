#ifndef __BULLETIN_H__
#define __BULLETIN_H__


#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

/**
* @brief Représente un bulletin générique.
*/
class Bulletin {

    private: 
        cpp_int pseudonym;  // Le pseudonyme (clé publique) de l'utilisateur.

    public:
        
        Bulletin(cpp_int pseudo) : pseudonym(pseudo) {};

        cpp_int get_pseudonym() { return pseudonym; };

        /**
        * @brief Affichage du bulletin.
        */
        virtual void cout_board() = 0;
    };

#endif // __BULLETIN_H__
