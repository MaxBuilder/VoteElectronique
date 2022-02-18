#include "../headers/RegionalAuthority.hpp"
#include "../headers/NationalBulletin.hpp"


int RegionalAuthority::get_id() { return id; }


NationalAuthority& RegionalAuthority::get_sup_auth() { return national_auth; }


void RegionalAuthority::transmit_results() {
    
    std::vector<Bulletin> national_board = get_sup_auth().get_bulletin_board().get_board();

    int id = get_id();
    cpp_int reg_sum = get_bulletin_board().get_sums()[0];
    cpp_int nat_prod = get_bulletin_board().get_sums()[1];

    NationalBulletin votes(id, reg_sum, nat_prod);

    national_board.push_back(votes);
}


void RegionalAuthority::cout_board() {
    std::cout << "Board de l'autorité régionale n°" << get_id() << " : " << std::endl;
    get_bulletin_board().cout_board();
}


void RegionalAuthority::make_tally() {
    // ToDo
    // cpp_int loc_sum_sum = 0;
    // cpp_int reg_prod_prod = 1;
    // cpp_int nat_prod_prod = 1;
    // for (size_t i = 0; i < get_bulletin_board().get_board().size(); i++)  {
    //     RegionalBulletin* casted_bulletin = (RegionalBulletin*) get_bulletin_board().get_board()[i];
    //     loc_sum_sum += casted_bulletin->get_loc_sum();
    //     reg_prod_prod *= casted_bulletin->get_reg_product(); // ToDo : Passer en produits modulaires [?]
    //     nat_prod_prod *= casted_bulletin->get_nat_product();
    // }
    // // Insertion des 3 valeurs calculées dans le tableau sums
    // get_bulletin_board().get_sums().insert(get_bulletin_board().get_sums().end(), {loc_sum_sum, reg_prod_prod, nat_prod_prod} );
}




// void RegionalAuthority::print_board() {
//     if (get_bulletin_board().get_board().size() > 0)  {
//         std::cout << "   Regional board: ("<< std::setfill(' ') << std::setw(2) << get_bulletin_board().get_board().size() << " entries)\n";
//         std::cout << "| Pseu. | loc_s | reg_p | nat_p |\n";
//         std::cout << "|-------|-------|-------|-------|\n";
//         for (size_t i = 0; i < get_bulletin_board().get_board().size(); i++)  {
//             RegionalBulletin* casted_bulletin = (RegionalBulletin*) get_bulletin_board().get_board()[i]; 
//             casted_bulletin->cout_board();
//         }
//         std::cout << "|-------|-------|-------|-------|\n";
//     }
//     else  {
//         std::cout << " > Regional board empty\n";
//     }

//     std::cout << "| Sums. | ";
//     for (size_t i = 0; i < get_bulletin_board().get_sums().size(); i++)  {
//         std::cout << std::setfill(' ') << std::setw(5) << get_bulletin_board().get_sums()[i] << " | ";
//     }
//     std::cout << "\n";
// }
