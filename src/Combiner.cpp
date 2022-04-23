#include "Combiner.hpp"


Combiner::Combiner(cpp_int sk_, PKey pk_, cpp_int delta_, cpp_int modulus, int nb_servers, cpp_int m) {
	sk = sk_;
	pk = pk_;
	delta = delta_;
	std::vector<cpp_int> secret_shares = generateSecretShares(nb_servers, modulus, m);

	for (int i = 1; i <= nb_servers; i++) {
		servers.push_back(new CryptoServer(i, delta_, secret_shares.at(i - 1), modulus));
	}
}


cpp_int Combiner::horner(std::vector<cpp_int> poly, cpp_int x)
{
	cpp_int result = poly[0];

	for (size_t i = 1; i < poly.size(); i++) {
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

	boost::random_device rn;
	boost::random::mt19937 mt(rn) ;
	boost::random::uniform_int_distribution<cpp_int> rand_gen(0, Nm - 1);

	std::vector<cpp_int> ai;
	ai.push_back(sk);	// a0 = sk
	for (int i = 0; i < nb_servers; i++)
		ai.push_back(rand_gen(mt));

	for (int i = 1; i <= nb_servers; i++)
		res.push_back(boost::multiprecision::powm(horner(ai, i), 1, Nm));

	return res;
}


void Combiner::calculateResults(cpp_int c)
{
	for (CryptoServer* server : servers)
	{
		results.push_back(server->computeDecryptionShare(c));
	}
}


cpp_int Combiner::calculateMu(int j)
{
	cpp_int res;
	double res_tmp = 1.;
	int nb_servers = servers.size();

	j++; // On considère les serveurs numérotés de 1 à N dans le calcul de Mu
	for (int j_prime = 1; j_prime < nb_servers+1; j_prime++)
	{
		if (j_prime == j)
			continue;
		res_tmp = res_tmp * (j_prime / (j_prime - j));
	}
	// En pratique delta devrait mesurer moins de 128 bits
	
	multiply(res, (cpp_int) res_tmp, delta);
	
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
	// ToDo: vérifier d'abord si t decryption shares sont valides

	std::cout << "\n > Combine func:\n";
	cpp_int res = 1;
	cpp_int N2;
	multiply(N2, pk.N, pk.N);

	cpp_int base;
	cpp_int exponent;
	for (size_t j = 0; j < servers.size(); j++)
	{
		std::cout << "\n   Serveur " << j << ":\n";
		cpp_int mu = calculateMu(j);
		std::cout << "mu: " << mu << "\n";

		multiply(exponent, mu, cpp_int(2)); // exponent: mu*2
		base = results[j];
		std::cout << "c_j: " << results[j] << ", N²: " << N2 <<"\n";
		if (exponent < 0) {
			// Si l'exposant est négatif, on calcule l'inverse modulaire en N2 de la base et on passe l'exposant positif
			std::cout << "Exposant négatif: on inverse la base " << base << " modulo " << N2 << "\n";
			base = boost::integer::mod_inverse(base, N2);
			if (base == 0)  {
				std::cout << "There is no inverse of base mod " <<N2<<"\n";
				return -1;
			}
			exponent = -exponent;
		}
		cpp_int tmp = powm(base, exponent, N2); // c_j ^ 2*mu
		std::cout << "c_j ^ 2*mu mod N²: " << tmp  << "\n";
		multiply(res, res, tmp);
	}
	std::cout << "\n   Before LFunc: res:" << res << "\n";
	res = Lfunction(res, pk.N);
	std::cout << "   After LFunc: res:" << res << "\n\n";

	cpp_int divider, delta2;
	cpp_int invDivider;
	multiply(divider, cpp_int(4), pk.tetha); // 4*Tetha
	multiply(delta2, delta, delta); // Delta^2
	multiply(divider, divider, delta2); // 4*Tetha*Delta^2
	
	std::cout << "tetha: " << pk.tetha << "\n";
	std::cout << "divider (4*Tetha*Delta^2): " << divider << "\n";

	divider = powm(divider, 1, pk.N); // divider mod N
	invDivider = boost::integer::mod_inverse(divider, pk.N);
	if (invDivider == 0)  {
		std::cout << "There is no inverse of "<< divider << " mod " <<pk.N<<"\n\n";
		return -1;
	}

	std::cout << "inverse de (4*Tetha*Delta^2) mod N: " << invDivider << "\n\n";
	multiply(res, res, invDivider);
	std::cout << "Résultat de combinaison: " << res << "\n";
	return res;
}
