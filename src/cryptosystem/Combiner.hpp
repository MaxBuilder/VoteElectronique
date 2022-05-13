#ifndef _COMBINER_H_
#define _COMBINER_H_

#include <vector>
#include <array>
#include <boost/random.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>
#include <boost/integer/mod_inverse.hpp>

#include "CryptoServer.hpp"
#include "CryptoUtils.hpp"

class Combiner
{

private:
	std::vector<CryptoServer *> servers; // Les serveurs de d�chiffrement

	int tval; // Valeur du seuil t
	
	cpp_int sk; // La cl� secr�te de l'autorit�.

	cpp_int delta; // Le param�tre delta (nombre de serveurs factoriel)

	PublicKey pk; // La cl� publique de l'autorit�. N�cessaire pour obtenir les param�tres dans les m�thodes suivantes.

	std::vector<cpp_int> results; // Vecteur qui contient les d�chiffrements partiels provenant des CryptoServers.

	/**
	 * @brief Utilis�e dans le constructeur du combiner afin de donner les "secrets shares" de la cle privee aux serveurs.
	 */
	std::vector<cpp_int> generateSecretShares(int nb_servers, int t, cpp_int N, cpp_int m);

	/**
	 * @Brief Algorithme de Horner permettant l'�valuation rapide d'un polyn�me.
	 *
	 * @return cpp_int l'�valuation du polyn�me P avec la valeur x.
	 */
	cpp_int horner(std::vector<cpp_int> poly, cpp_int x);

	/*
	 * @Brief Calcul de l'exposant mu_0 pour l'algo de combinaison
	 */
	cpp_int calculateMu(int j);

	/*
	 * La fonction L du cryptosyst�me de Paillier.
	 */
	cpp_int Lfunction(cpp_int u, cpp_int N);

public:
	// Constructeur
	Combiner(cpp_int sk_, PKey pk_, cpp_int delta_, cpp_int modulus, int nb_servers, int t, cpp_int m);

	/*
	 * @brief Génère les d�chiffrements partiels.
	 */
	void calculateResults(cpp_int c);

	/*
	 * @Brief La combinason des d�chiffr�s partiels.
	 */
	cpp_int combine();
};

#endif
