#ifndef _COMBINER_H_
#define _COMBINER_H_

#include <vector>
#include <array>

#include "CryptoServer.hpp"


class Combiner {

private:
	
	std::vector<CryptoServer *> servers;	// Les serveurs de déchiffrement

	cpp_int sk; // La clé secrète de l'autorité.


	/**
	* @brief Utilisee dans le constructeur du combiner afin de donner les "secrets shares" de la cle privee aux serveurs.
	*/
	std::vector<cpp_int> generateSecretShares(int nb_servers);

public:

	// Constructeur
	Combiner(cpp_int sk_, cpp_int delta_, cpp_int modulus, int nb_servers);

};

#endif
