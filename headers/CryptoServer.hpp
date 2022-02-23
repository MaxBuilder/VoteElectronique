#ifndef _CRYPTOSERVER_H_
#define _CRYPTOSERVER_H_

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class CryptoServer {

private:

	int id;	// Le num�ro du serveur associe au combineur.

	cpp_int delta; // Delta = (nombre de serveurs)!

	cpp_int sk;	// La "secret share" qui lui a �t� attribu�e.

	cpp_int N; // Le modulo des calculs.


public:

	// Constructeur
	CryptoServer(int id_, cpp_int delta_, cpp_int sk_, cpp_int N_) : id(id_), delta(delta_), sk(sk_), N(N_) {};

	
	/**
	* @brief Calcule la "decryption share" gr�ce � la "secret share" (attribut sk) et au chiffr� global pass� en argument.
	* 
	* @return cpp_int le d�chiffrement partiel du chiffr� c.
	*/
	cpp_int computeDecryptionShare(cpp_int c);


	/**
	* @brief Retourne le num�ro du serveur.
	* 
	* @return int le num�ro du serveur.
	*/
	int getId();

};

#endif