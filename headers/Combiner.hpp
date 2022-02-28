#ifndef _COMBINER_H_
#define _COMBINER_H_

#include <vector>
#include <array>
#include <boost/random.hpp>

#include "CryptoServer.hpp"
#include "CryptoUtils.hpp"


class Combiner {

private:
	
	std::vector<CryptoServer *> servers;	// Les serveurs de déchiffrement

	cpp_int sk; // La clé secrète de l'autorité.

	PublicKey pk; // La clé publique de l'autorité. Nécessaire pour obtenir les paramètres dans les méthodes suivantes.


	/**
	* @brief Utilisee dans le constructeur du combiner afin de donner les "secrets shares" de la cle privee aux serveurs.
	*/
	std::vector<cpp_int> generateSecretShares(int nb_servers, cpp_int N, cpp_int m);


	/**
	* @Brief Algorithme de Horner permettant l'évaluation rapide d'un polynôme.
	*
	* @return cpp_int l'évaluation du polynôme P avec la valeur x.
	*/
	cpp_int horner(std::vector<cpp_int> poly, cpp_int x);


public:

	// Constructeur
	Combiner(cpp_int sk_, cpp_int delta_, cpp_int modulus, int nb_servers, cpp_int m);

};

#endif
