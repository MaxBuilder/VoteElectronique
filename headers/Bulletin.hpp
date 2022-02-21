#ifndef __BULLETIN_H__
#define __BULLETIN_H__


#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

/**
* @brief Repr�sente un bulletin g�n�rique.
*/
class Bulletin {

    private: 
        cpp_int pseudonym;  // Le pseudonyme (cl� publique) de l'utilisateur.

    public:
        
        Bulletin(cpp_int pseudo) : pseudonym(pseudo) {};

        cpp_int get_pseudonym() { return pseudonym; };

        /**
        * @brief Affichage du bulletin.
        */
        virtual void cout_board() = 0;
    };

#endif // __BULLETIN_H__
