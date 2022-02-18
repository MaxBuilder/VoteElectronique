#ifndef __REGIONAL_BULLETIN_H__
#define __REGIONAL_BULLETIN_H__

#include "Bulletin.hpp"

/**
* @brief Représente un bulletin issu d'une autorité régionale.
*/
class RegionalBulletin : public Bulletin {


private:
    cpp_int loc_sum; // La somme des votes locaux en clair.

    cpp_int reg_product; // Le produit des votes r�gionaux.

    cpp_int nat_product; // Le produit des votes nationaux.

public:

    // Constructeur
    RegionalBulletin(cpp_int pseudo, cpp_int a, cpp_int b, cpp_int c) : Bulletin(pseudo), loc_sum(a), reg_product(b), nat_product(c) {}


    /**
    * @brief Accesseur sur l'attribut loc_sum.
    * @return cpp_int l'attribut loc_sum.
    */
    cpp_int get_loc_sum();


    /**
    * @brief Accesseur sur l'attribut reg_sum.
    * @return cpp_int l'attribut reg_sum.
    */
    cpp_int get_reg_product();


    /**
    * @brief Accesseur sur l'attribut nat_sum.
    * @return cpp_int l'attribut nat_sum.
    */
    cpp_int get_nat_product();


    void cout_board() override;
};

#endif // __REGIONAL_BULLETIN_H__
