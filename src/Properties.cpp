#include "../headers/Properties.hpp"


Properties * Properties::reference = nullptr;


Properties::Properties() {

	// Lecture et parsing du fichier de configuration
	ifstream ifs("config.json");
	Json::Reader reader;
	Json::Value obj;
	reader.parse(ifs, obj);

	// Initialisation des attributs avec les valeurs des props.
	nbVoters = obj["nbVoters"].asInt();
	nbRegionalAuth = obj["nbRegionalAuth"].asInt();
	nbLocalPerRegionalAuth = obj["nbLocalPerRegionalAuth"].asInt();
	nbServersPerCombiner = obj["nbServersPerCombiner"].asInt();

	// Calcul de la factorielle pour delta (on le fait une seule fois pour toute l'appli)
	delta = 1;
	for (cpp_int i = 2; i <= nbServersPerCombiner; i++)
		multiply(delta, delta, i);

}


Properties*  Properties::getProperties() {

	if (reference == nullptr) {
		// Initialisation du pointeur
		reference = new Properties();
	}
	return reference;
}


int Properties::get_nbVoters() { return nbVoters; }


int Properties::get_nbRegionalAuth() { return nbRegionalAuth; }


int Properties::get_nbLocalPerRegionalAuth() { return nbLocalPerRegionalAuth; }


int Properties::get_nbServersPerCombiner() { return nbServersPerCombiner; }


cpp_int Properties::get_delta() { return delta; };