#include "Properties.hpp"

using Json = nlohmann::json;

Properties *Properties::reference = nullptr;

Properties::Properties()
{

	// Lecture et parsing du fichier de configuration
	std::ifstream ifs("config.json");
	Json jf = Json::parse(ifs);

	// Initialisation des attributs avec les valeurs des props.
	nbVoters = jf["nbVoters"];
	nbRegionalAuth = jf["nbRegionalAuth"];
	nbLocalPerRegionalAuth = jf["nbLocalPerRegionalAuth"];
	nbCandidats = jf["nbCandidats"];
	nbServersPerCombiner = jf["nbServersPerCombiner"];
	t = jf["t"];
	voteDuration = jf["voteDuration"];

	// Calcul de la factorielle pour delta (on le fait une seule fois pour toute l'appli)
	delta = 1;
	for (cpp_int i = 2; i <= nbServersPerCombiner; i++)
		multiply(delta, delta, i);
}

Properties *Properties::getProperties()
{

	if (reference == nullptr)
	{
		// Initialisation du pointeur
		reference = new Properties();
	}
	return reference;
}

int Properties::get_nbVoters() { return nbVoters; }

int Properties::get_nbRegionalAuth() { return nbRegionalAuth; }

int Properties::get_nbLocalPerRegionalAuth() { return nbLocalPerRegionalAuth; }

int Properties::get_nbCandidats() { return nbCandidats; }

int Properties::get_nbServersPerCombiner() { return nbServersPerCombiner; }
int Properties::get_t() { return t; }

cpp_int Properties::get_delta() { return delta; };

double Properties::getVoteDuration() { return voteDuration; }
time_t Properties::getVoteStart() { return voteStart; };
time_t Properties::getVoteEnd() { return voteEnd; };

void Properties::setVoteStart(time_t vs) { voteStart = vs; };
void Properties::setVoteEnd(time_t es) { voteEnd = es; };