#include <tuple>

#include <Bulletin.hpp>


class LocalBulletin : public Bulletin {
private:
    time_t timestamp;
    std::tuple<cpp_int, cpp_int, cpp_int> loc_vote;
    std::tuple<cpp_int, cpp_int, cpp_int> reg_vote;
    std::tuple<cpp_int, cpp_int, cpp_int> nat_vote;
    cpp_int equ_proof;

public:
    time_t get_timestamp();
    std::tuple<cpp_int, cpp_int, cpp_int> get_loc_vote();
    std::tuple<cpp_int, cpp_int, cpp_int> get_reg_vote();
    std::tuple<cpp_int, cpp_int, cpp_int> get_nat_vote();
    cpp_int get_equ_proof();

    virtual void cout_board() {
        std::cout << " > LocalBulletin: " << get_pseudonym() << ", " << timestamp << ", " << std::get<0>(loc_vote) << std::endl;
    }

    virtual ~LocalBulletin() {};
};

