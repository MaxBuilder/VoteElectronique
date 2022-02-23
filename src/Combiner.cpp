#include "../headers/Combiner.hpp"


Combiner::Combiner(cpp_int sk_, cpp_int delta_, cpp_int modulus, int nb_servers) {
	sk = sk_;

	std::vector<cpp_int> secret_shares = generateSecretShares(nb_servers);

	for (int i = 1; i <= nb_servers; i++) {
		CryptoServer serv(i, delta_, secret_shares.at(i - 1), modulus);
		servers.push_back(&serv);
	}
}


std::vector<cpp_int> Combiner::generateSecretShares(int nb_servers) {
	// ToDo
	std::vector<cpp_int> res;
	res.push_back(1);
	return res;
}