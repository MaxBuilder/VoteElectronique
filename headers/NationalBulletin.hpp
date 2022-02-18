#ifndef __NATIONAL_BULLETIN_H__
#define __NATIONAL_BULLETIN_H__

#include "Bulletin.hpp"

/**
* @brief Repr�sente un bulletin issu d'une autorit� r�gionale.
*/
class NationalBulletin : public Bulletin {

private:
    cpp_int reg_sum; // La somme des votes locaux en clair.
    
    cpp_int nat_product; // Le produit des votes chiffr�s nationaux fournis par les autorit�s locales.

public:

    // Constructeur
    NationalBulletin(cpp_int pseudo, cpp_int reg_sum_, cpp_int nat_product_) : Bulletin(pseudo), reg_sum(reg_sum_), nat_product(nat_product_) {}

    /**
    * @brief Accesseur sur la somme des votes locaux en clair.
    * @return cpp_int la somme des votes locaux en clair.
    */
    cpp_int get_reg_sum();


    /**
    * @brief Accesseur sur le produit des votes nationaux.
    * @return cpp_int le produit des votes nationaux.
    */
    cpp_int get_nat_product();


    void cout_board() override;
};

#endif // __NATIONAL_BULLETIN_H__