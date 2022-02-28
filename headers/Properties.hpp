#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include <iostream>
#include <fstream>
#include <json/json.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

class Properties {

private:

	int nbVoters; // Le nombre de votants.
	int nbRegionalAuth; // Le nombre d'autorit�s r�gionales.
	int nbLocalPerRegionalAuth; // Le nombre d'autorit�s locales par autorit� r�gionale.

	int nbServersPerCombiner; // Le nombre de serveurs de d�chiffrement par combineur.
	cpp_int delta; // (nbServersPerCombiner)!


protected:

	static Properties* reference;	// Le pointeur sur l'unique objet (DP Singleton)

	//Constructeur
	Properties();

public:

	Properties(Properties& other) = delete;	// Pas clonable
	

	void operator=(const Properties&) = delete; // Pas de construction de copie par affectation


	/**
	* @brief Met en place le DP singleton. S'assure qu'il y a toujours une unique instance de la classe.
	* Renvoie la r�f�rence vers l'objet s'il existe, ou bien le cr�e dans le cas contraire.
	*/
	static Properties* getProperties();


	// A la suite se trouvent les diff�rents accesseurs sur les propri�t�s.

	int get_nbVoters();

	int get_nbRegionalAuth();

	int get_nbLocalPerRegionalAuth();

	int get_nbServersPerCombiner();

	cpp_int get_delta();
};

#endif
