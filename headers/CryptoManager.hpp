#ifndef _CRYPTOMANAGER_H_
#define _CRYPTOMANAGER_H_

#include <tuple>
#include <boost/multiprecision/cpp_int.hpp>

#include "CryptoUtils.hpp"
#include "Combiner.hpp"
//#include "Verifier.hpp"

class CryptoManager {

private:

	Combiner combiner;	// Le combineur
	//Verifier verifier;	// Le vérifieur de preuve

public:

	/**
	* @brief Genere la paire de cles (publique, privee) de l'autorite.
	* 
	* @return std::tuple<PKey, boost::multiprecision::cpp_int> la paire de cles (publique, privee) de l'autorite.
	*/
	/*ToDo : std::tuple<PKey, boost::multiprecision::cpp_int> KeyGeneration();*/


	/**
	* @brief Permet d'accéder au combineur associe à l'autorite.
	* 
	* @return Combiner & le combineur associe à l'autorite.
	*/
	Combiner & getCombiner();


	//ToDo : Verifier & getVerifier
};

#endif
