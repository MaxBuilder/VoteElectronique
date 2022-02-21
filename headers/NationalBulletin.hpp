
#include "Bulletin.hpp"

/**
* @brief Représente un bulletin issu d'une autorité régionale.
*/
class NationalBulletin : public Bulletin {

private:
    cpp_int reg_sum; // La somme des votes locaux en clair.
    
    cpp_int nat_product; // Le produit des votes chiffrés nationaux fournis par les autorités locales.

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
