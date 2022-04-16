#include "Combiner.hpp"


Combiner::Combiner(cpp_int sk_, cpp_int delta_, cpp_int modulus, int nb_servers, cpp_int m) {
	sk = sk_;
	delta = delta_;

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


std::vector<cpp_int> Combiner::getResults(cpp_int c)
{
	for (CryptoServer* server : servers)
	{
		cpp_int res = server->computeDecryptionShare(c);
		results.push_back(res);
	}
}


cpp_int Combiner::calculateMu(int j)
{
	cpp_int res;
	double res_tmp = 1.;
	int nb_servers = servers.size();
	
	for (int j_prime = 0; j_prime < nb_servers; j_prime++)
	{
		if (j_prime == j)
			continue;

		res_tmp = res_tmp * (j_prime / (j_prime - j));
	}

	long long delta_ = (long long)delta; // En pratique delta devrait mesurer moins de 128 bits
	res = cpp_int(delta_ * res_tmp);
	return res;
}


cpp_int Combiner::Lfunction(cpp_int u, cpp_int N)
{
	cpp_int res;
	subtract(res, u, cpp_int(1));
	return res / N;
}


cpp_int Combiner::combine()
{
	cpp_int res = 1;
	cpp_int N2;
	multiply(N2, pk.N, pk.N);

	for (int j = 0; j < servers.size(); j++)
	{
		cpp_int power;
		cpp_int mu = calculateMu(j);
		multiply(power, mu, cpp_int(2));
		cpp_int tmp = powm(results[j], power, N2);
		multiply(res, res, tmp);
	}

	res = Lfunction(res, pk.N);

	cpp_int divider, delta2;
	multiply(divider, cpp_int(4), pk.tetha);
	multiply(delta2, delta, delta);
	multiply(divider, divider, delta2);

	res = res / divider;
	return res;
}