#ifndef _PROPERTIES_H_
#define _PROPERTIES_H_

#include <iostream>
#include <fstream>
// #include <nlohmann/json.hpp>
#include "json.hpp"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class Properties
{

private:
	bool boardFiles; 	// Booléen indiquant s'il est nécessaire d'exporter les fichiers des bulletin boards
	int nbVotersPerLocalAuth;	// Le nombre de votants.
	int nbRegionalAuth;			// Le nombre d'autorités régionales.
	int nbLocalPerRegionalAuth; // Le nombre d'autorités locales par autorité régionale.
	int nbCandidats;			// Le nombre de candidats présentés au vote

	int keySize;
	int nbServersPerCombiner; // Le nombre de serveurs de déchiffrement par combineur.
	int t;					  // Sachant t-1 le nombre minimum de serveurs qui doivent réussir leur déchiffrement partiel pour la combinaison
	cpp_int delta;			  // (nbServersPerCombiner)!

	double voteDuration; // Durée du vote en millisecondes
	time_t voteStart;	 // Timestamp du début de vote
	time_t voteEnd;		 // Timestamp de fin de vote
protected:
	static Properties *reference; // Le pointeur sur l'unique objet (DP Singleton)

	// Constructeur
	Properties();

public:
	Properties(Properties &other) = delete; // Pas clonable

	void operator=(const Properties &) = delete; // Pas de construction de copie par affectation

	/**
	 * @brief Met en place le DP singleton. S'assure qu'il y a toujours une unique instance de la classe.
	 * Renvoie la référence vers l'objet s'il existe, ou bien le crée dans le cas contraire.
	 */
	static Properties *getProperties();

	// A la suite se trouvent les différents accesseurs sur les propriétés.
	bool get_boardFiles();

	int get_nbVotersPerLocalAuth();

	int get_nbRegionalAuth();

	int get_nbLocalPerRegionalAuth();

	int get_nbCandidats();

	int get_keySize();

	int get_nbServersPerCombiner();
	int get_t();

	cpp_int get_delta();

	double getVoteDuration();
	time_t getVoteStart();
	time_t getVoteEnd();

	void setVoteStart(time_t);
	void setVoteEnd(time_t);
};

#endif
