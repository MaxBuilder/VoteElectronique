#include "NationalAuthority.hpp"

std::vector<cpp_int> NationalAuthority::calculate_results(cpp_int M, int p, cpp_int N)
{

    cpp_int M_modN = boost::multiprecision::powm(M, 1, N);

    cpp_int final_tally = get_bulletin_board().get_sums().at(0);
    std::vector<cpp_int> res;

    for (int i = 0; i < p; i++)
    {
        cpp_int q;
        cpp_int r;
        boost::multiprecision::divide_qr(final_tally, M_modN, q, r);
        final_tally = q;
        r = boost::multiprecision::powm(final_tally, 1, M_modN);
        boost::multiprecision::subtract(final_tally, final_tally, r);
        res.push_back(r);
    }

    return res;
}

void NationalAuthority::transmit_results()
{

    Properties *prop = Properties::getProperties();
    int nb_voters = prop->get_nbRegionalAuth() * prop->get_nbLocalPerRegionalAuth() * prop->get_nbVotersPerLocalAuth();
    int bitsize = (int)boost::multiprecision::msb(nb_voters) + 1;
    cpp_int M = boost::multiprecision::pow(cpp_int(2), bitsize);
    std::vector<cpp_int> res = calculate_results(M, prop->get_nbCandidats(), get_public_key().N);

    for (size_t i = 0; i < res.size(); i++)
    {
        std::cout << "	Candidat n°" << i + 1 << " : " << res[i] << " votes\n";
    }
    std::cout << "\n"
              << "\033[1;32mLe candidat n°"
              << std::max_element(res.begin(), res.end()) - res.begin() + 1
              << " remporte l'élection avec "
              << *std::max_element(res.begin(), res.end()) << " voix décomptées !\033[0m\n";
}

void NationalAuthority::cout_board()
{
    std::cout << "	\033[;34mBoard de l'autorité nationale :\033[00m\n";
    std::cout << "	\033[1m| IdAut |  Regional sums  | National prods  |\n\033[0m";
    get_bulletin_board().cout_board();

    std::cout << "	\033[1m| Sums. | ";
    for (size_t i = 0; i < get_bulletin_board().get_sums().size(); i++)
    {
        std::cout << std::setfill(' ') << std::setw(15) << std::hex << get_bulletin_board().get_sums()[i] 
        << " | " << std::dec;
    }
    std::cout << "\n\033[0m";
}

bool NationalAuthority::make_tally()
{
    cpp_int N = get_public_key().N; 
    cpp_int nat_N2;
    boost::multiprecision::multiply(nat_N2, N, N);

    cpp_int reg_sum = 0;
    cpp_int nat_prod = 1;

    for (Bulletin *b : get_bulletin_board().get_board())
    {

        NationalBulletin *pt_b = (NationalBulletin *)b;

        cpp_int reg_vote = pt_b->get_reg_sum();
        boost::multiprecision::add(reg_sum, reg_sum, reg_vote);
        reg_sum = boost::multiprecision::powm(reg_sum, 1, N); // Somme des déchiffrements en mod N

        cpp_int nat_vote = pt_b->get_nat_product();
        boost::multiprecision::multiply(nat_prod, nat_prod, nat_vote);
        nat_prod = boost::multiprecision::powm(nat_prod, 1, nat_N2);
    }

    // Somme des résultats régionaux
    get_bulletin_board().get_sums().push_back(reg_sum);

    // Déchiffrement de la somme nationale
    get_combiner().calculateResults(nat_prod);
    cpp_int decrypted_nat_prod = get_combiner().combine();
    get_bulletin_board().get_sums().push_back(decrypted_nat_prod);

    // Comparaison de la somme des résultats régionaux au déchiffrement national
    return reg_sum == decrypted_nat_prod;
}
