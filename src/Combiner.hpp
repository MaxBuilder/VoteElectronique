#ifndef _COMBINER_H_
#define _COMBINER_H_

#include <vector>
#include <array>
#include <boost/random.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

#include "CryptoServer.hpp"
#include "CryptoUtils.hpp"


class Combiner {

private:
	
	std::vector<CryptoServer *> servers;	// Les serveurs de déchiffrement

	cpp_int sk; // La clé secrète de l'autorité.

	cpp_int delta; // Le paramètre delta (nombre de serveurs factoriel) 

	PublicKey pk; // La clé publique de l'autorité. Nécessaire pour obtenir les paramètres dans les méthodes suivantes.

	std::vector<cpp_int> results; // Vecteur qui contient les déchiffrements partiels provenant des CryptoServers. 


	/**
	* @brief Utilisée dans le constructeur du combiner afin de donner les "secrets shares" de la cle privee aux serveurs.
	*/
	std::vector<cpp_int> generateSecretShares(int nb_servers, cpp_int N, cpp_int m);


	/**
	* @Brief Algorithme de Horner permettant l'évaluation rapide d'un polynôme.
	*
	* @return cpp_int l'évaluation du polynôme P avec la valeur x.
	*/
	cpp_int horner(std::vector<cpp_int> poly, cpp_int x);

	/*
	* @Brief Calcul de l'exposant mu_0 pour l'algo de combinaison
	*/
	cpp_int calculateMu(int j);

	/*
	* La fonction L du cryptosystème de Paillier.
	*/
	cpp_int Lfunction(cpp_int u, cpp_int N);

public:

	// Constructeur
	Combiner(cpp_int sk_, cpp_int delta_, cpp_int modulus, int nb_servers, cpp_int m);

	/*
	* @brief Récupère les déchiffrements partiels.
	*/
	std::vector<cpp_int> getResults(cpp_int c);

	/*
	* @Brief La combinason des déchiffrés partiels.
	*/
	cpp_int combine();

};

#endif
