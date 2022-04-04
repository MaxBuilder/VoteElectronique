#include "Combiner.hpp"


Combiner::Combiner(cpp_int sk_, cpp_int delta_, cpp_int modulus, int nb_servers, cpp_int m) {
	sk = sk_;

	std::vector<cpp_int> secret_shares = generateSecretShares(nb_servers, modulus, m);

	for (int i = 1; i <= nb_servers; i++) {
		CryptoServer serv(i, delta_, secret_shares.at(i - 1), modulus);
		servers.push_back(&serv);
	}
}


cpp_int Combiner::horner(std::vector<cpp_int> poly, cpp_int x)
{
	cpp_int result = poly[0];

	for (auto i = 1; i < poly.size(); i++) {
		boost::multiprecision::multiply(result, result, x);
		boost::multiprecision::add(result, result, poly[i]);
	}

	return result;
}


std::vector<cpp_int> Combiner::generateSecretShares(int nb_servers, cpp_int N, cpp_int m) {
	
	cpp_int Nm;
	boost::multiprecision::multiply(Nm, N, m);
	cpp_int Nm_len = boost::multiprecision::msb(Nm); // Le nombre de bits de Nm


	std::vector<cpp_int> res;

	boost::random::mt19937 mt;
	boost::random::uniform_int_distribution<cpp_int> rand_gen(0, Nm - 1);

	std::vector<cpp_int> ai;
	ai.push_back(sk);	// a0 = sk
	for (int i = 0; i < nb_servers; i++)
		ai.push_back(rand_gen(mt));

	for (int i = 1; i <= nb_servers; i++)
		res.push_back(boost::multiprecision::powm(horner(ai, i), 1, Nm));

	return res;
}