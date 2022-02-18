#include "../headers/NationalAuthority.hpp"

void NationalAuthority::transmit_results() {
    // ToDo: extraction du résultat du vote depuis la somme claire
    return;
}


void NationalAuthority::cout_board() {
    std::cout << "Board de l'autorité nationale : " << std::endl;
    get_bulletin_board().cout_board();
}



void NationalAuthority::make_tally() {
    // ToDo
    // cpp_int reg_sum_sum = 0;
    // cpp_int nat_prod_prod = 1;
    // for (size_t i = 0; i < get_bulletin_board().get_board().size(); i++)  {
    //     NationalBulletin* casted_bulletin = (NationalBulletin*) get_bulletin_board().get_board()[i];
    //     reg_sum_sum += casted_bulletin->get_reg_sum();
    //     nat_prod_prod *= casted_bulletin->get_nat_product(); // ToDo : Passer en produits modulaires [?]
    // }
    // // Insertion des 2 valeurs calculées dans le tableau sums
    // get_bulletin_board().get_sums().push_back(reg_sum_sum);
    // get_bulletin_board().get_sums().push_back(nat_prod_prod);
}


// void NationalAuthority::print_board() {
//     if (get_bulletin_board().get_board().size() > 0)  {
//         std::cout << "   National board: ("<< std::setfill(' ') << std::setw(2) << get_bulletin_board().get_board().size() << " entries)\n";
//         std::cout << "| Pseu. | reg_s | nat_p |       |\n";
//         std::cout << "|-------|-------|-------|-------|\n";
//         for (size_t i = 0; i < get_bulletin_board().get_board().size(); i++)  {
//             NationalBulletin* casted_bulletin = (NationalBulletin*) get_bulletin_board().get_board()[i]; 
//             casted_bulletin->cout_board();
//         }
//         std::cout << "|-------|-------|-------|-------|\n";
//     }
//     else  {
//         std::cout << " > National board empty\n";
//     }

//     std::cout << "| Sums. | ";
//     for (size_t i = 0; i < get_bulletin_board().get_sums().size(); i++)  {
//         std::cout << std::setfill(' ') << std::setw(5) << get_bulletin_board().get_sums()[i] << " | ";
//     }
//     std::cout << "\n";
// }
