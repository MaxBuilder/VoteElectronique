#include "../headers/RegionalAuthority.hpp"


void RegionalAuthority::transmit_results() {
    return;
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
