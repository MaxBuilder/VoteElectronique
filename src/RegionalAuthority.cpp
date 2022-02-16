#include "../headers/RegionalAuthority.hpp"

// ToDo : process transmission de résultats à confirmer ou modifier (voir autre todo)
void RegionalAuthority::receive_results(cpp_int loc_id, std::vector<cpp_int> sums) {
    get_bulletin_board().get_board().push_back( new RegionalBulletin(loc_id, sums[0], sums[1], sums[2]) );
};


void RegionalAuthority::make_tally() {
    cpp_int loc_sum_sum = 0;
    cpp_int reg_prod_prod = 1;
    cpp_int nat_prod_prod = 1;
    for (size_t i = 0; i < get_bulletin_board().get_board().size(); i++)  {
        RegionalBulletin* casted_bulletin = (RegionalBulletin*) get_bulletin_board().get_board()[i];
        loc_sum_sum += casted_bulletin->get_loc_sum();
        reg_prod_prod *= casted_bulletin->get_reg_product(); // ToDo : Passer en produits modulaires [?]
        nat_prod_prod *= casted_bulletin->get_nat_product();
    }
    // Insertion des 3 valeurs calculées dans le tableau sums
    get_bulletin_board().get_sums().insert(get_bulletin_board().get_sums().end(), {loc_sum_sum, reg_prod_prod, nat_prod_prod} );
}

void RegionalAuthority::transmit_results() {
    // Récupère son tableau Sums et l'écrit dans sa ligne (son ID) sur le board de la régionale
    // ToDo : moyen de bloquer l'écriture sur les autres lignes que la sienne
    // ToDo : pseudo des locales = id ? 
    get_national_auth().receive_results(get_id(), get_bulletin_board().get_sums());
}


void RegionalAuthority::print_board() {
    if (get_bulletin_board().get_board().size() > 0)  {
        std::cout << "   Regional board: ("<< std::setfill(' ') << std::setw(2) << get_bulletin_board().get_board().size() << " entries)\n";
        std::cout << "| Pseu. | loc_s | reg_p | nat_p |\n";
        std::cout << "|-------|-------|-------|-------|\n";
        for (size_t i = 0; i < get_bulletin_board().get_board().size(); i++)  {
            RegionalBulletin* casted_bulletin = (RegionalBulletin*) get_bulletin_board().get_board()[i]; 
            casted_bulletin->cout_board();
        }
        std::cout << "|-------|-------|-------|-------|\n";
    }
    else  {
        std::cout << " > Regional board empty\n";
    }

    std::cout << "| Sums. | ";
    for (size_t i = 0; i < get_bulletin_board().get_sums().size(); i++)  {
        std::cout << std::setfill(' ') << std::setw(5) << get_bulletin_board().get_sums()[i] << " | ";
    }
    std::cout << "\n";
}
