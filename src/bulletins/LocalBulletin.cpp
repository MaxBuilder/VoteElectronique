#define _CRT_SECURE_NO_WARNINGS

#include "LocalBulletin.hpp"

time_t LocalBulletin::get_timestamp() { return timestamp; }


std::tuple<cpp_int, cpp_int, cpp_int> LocalBulletin::get_loc_vote() { return loc_vote; }


std::tuple<cpp_int, cpp_int, cpp_int>  LocalBulletin::get_reg_vote() { return reg_vote; }


std::tuple<cpp_int, cpp_int, cpp_int> LocalBulletin::get_nat_vote() { return nat_vote; }


CryptoUtils::PKeyRSA LocalBulletin::get_pkey_RSA() { return pk; }


EqProof LocalBulletin::get_equ_proof() { return equ_proof; }


void LocalBulletin::cout_board() {
	// std::cout << timestamp << " | " << std::ctime(&timestamp) 
        // << "| " << std::setfill(' ') << std::setw(5) << get_pseudonym() << " | " << std::setfill(' ')
        // << std::setw(5) << std::get<0>(loc_vote) << " | " << std::setfill(' ') << std::setw(5) << std::get<1>(loc_vote) << " | "
        // << std::setfill(' ') << std::setw(5) << std::get<2>(loc_vote) << " |\n";

        std::tm *tm = std::localtime(&timestamp);
        std::cout << "| " 
        << std::setfill('0') << std::setw(2) << tm->tm_hour
        << ':' << std::setfill('0') << std::setw(2) << tm->tm_min 
        << ':' << std::setfill('0') << std::setw(2) << tm->tm_sec
        << " | " << std::setfill(' ') << std::setw(5) << get_pseudonym() << " | " << std::setfill(' ');
        
        

        std::cout << std::setw(5) << std::get<0>(loc_vote) << " | "
        << std::setw(5) << std::get<0>(reg_vote) << " | "
        << std::setw(5) << std::get<0>(nat_vote) << " | ";

        if (!valid)
                std::cout << "✅";
        else if (valid == 1)
                std::cout << "❌ Invalid timestamp";
        else if (valid == 2)
                std::cout << "❌ Invalid vote signature";
        else if (valid == 3)
                std::cout << "❌ Invalid vote proof";
        else if (valid == 4)
                std::cout << "❌ Invalid equality proof";
        else
                std::cout << "❌ Invalid";

        std::cout << "\n";
}
