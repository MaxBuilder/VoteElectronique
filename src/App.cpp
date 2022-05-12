#include "App.hpp"

App *App::reference = nullptr;

App::App() {
	Properties *prop = Properties::getProperties();
	std::cout << "\033[1;32mSimulation d'une session de vote électronique\033[0m\n";
	
	// Enregistrement du timestamp de début de vote
	auto start = std::chrono::system_clock::now();
	std::time_t start_time = std::chrono::system_clock::to_time_t(start);
	prop->setVoteStart(start_time);

	// Calcule le timestamp de fin de vote
	double voteDuration = prop->getVoteDuration();
	std::time_t end_time = start_time + voteDuration / 1000;
	prop->setVoteEnd(end_time);
	std::string start_time_string(std::ctime(&(start_time)));
	std::string end_time_string(std::ctime(&end_time));
	std::cout << "Période: \033[0;33m" << start_time_string.substr(0, start_time_string.length() - 1)
				<< "\033[0m au \033[0;33m" << end_time_string.substr(0, end_time_string.length() - 1)
				<< "\033[0m (" << voteDuration / 1000 / 60 << "mn)\n\n";

	
	nb_voters = prop->get_nbRegionalAuth() * prop->get_nbLocalPerRegionalAuth() * prop->get_nbVotersPerLocalAuth();
	nb_authorities = prop->get_nbLocalPerRegionalAuth() * prop->get_nbRegionalAuth() + prop->get_nbRegionalAuth()+1;
	int bitsize = (int)boost::multiprecision::msb(nb_voters) + 1;
	M = boost::multiprecision::pow(cpp_int(2), bitsize); 
	
	std::cout << "\033[1;33mConfiguration:\033[0m\n" 
				<< " - " << std::setfill(' ') << std::setw(4) << prop->get_nbCandidats() << " candidats\n"
				<< " - " << std::setfill(' ') << std::setw(4) << prop->get_nbRegionalAuth() << " autorité(s) régionale(s)\n" 
				<< " - " << std::setfill(' ') << std::setw(4) << prop->get_nbLocalPerRegionalAuth() << " autorité(s) locale(s) pour chaque autorité régionale\n" 
				<< " - " << std::setfill(' ') << std::setw(4) << prop->get_nbVotersPerLocalAuth() << " électeurs pour chaque autorité locale\n" 
				<< " - " << std::setfill(' ') << std::setw(4) << nb_voters << " électeurs au total\n"
				<< " - " << std::setfill(' ') << std::setw(4) << nb_authorities << " autorités au total\n"
				<< " - " << std::setfill(' ') << std::setw(4) << prop->get_nbServersPerCombiner() << " serveurs de déchiffrement pour chaque autorité (t = " << prop->get_t() << ")\n"
				<< " - " << std::setfill(' ') << std::setw(4) << prop->get_keySize() << " bits de clé privée pour chaque autorité\n";
	std::cout << "\n";
}

App *App::getApp() {
	if (reference == nullptr) {
		// Initialisation du pointeur
		reference = new App();
	}
	return reference;
}

void App::instanciate_authorities() {
	Properties *prop = Properties::getProperties();

	std::cout << "\033[1;33m ❯ Génération des autorités régionales:\033[0m\n";
	// Génération des autorités régionales
	for (int i = 0; i < prop->get_nbRegionalAuth(); i++) {
		reg_auths.push_back(RegionalAuthority(i + 1, nat_auth));
	}

	std::cout << "\033[1;33m ❯ Génération des autorités locales:\033[0m\n";
	// Génération des autorités locales
	for (size_t i = 0; i < reg_auths.size(); i++) {
		for (int j = 0; j < prop->get_nbLocalPerRegionalAuth(); j++) {
			loc_auths.push_back(LocalAuthority(j + 1, reg_auths[i]));
		}
	}
	std::cout << "\n";
}

void App::generate_random_votes() {
	Properties *prop = Properties::getProperties();

	std::cout << "\033[1;33m ❯ Génération de votes aléatoires chiffrés dans les boards des autorités locales:\033[0m\n";
	// Génération de votes aléatoires chiffrés dans les boards des autorités locales
	int choix;
	cpp_int vote;
	std::array<PublicKey, 3> pkeys;
	std::vector<int> clear_clear_votes;

	for (int i = 0; i < prop->get_nbCandidats(); i++)
		clear_clear_votes.push_back(0);

	// std::vector<cpp_int> clear_local_votes;
	std::vector<Client*> clients;

	// Générations de votes aléatoires
	for (size_t i = 0; i < loc_auths.size(); i++) {
		for (int j = 0; j < prop->get_nbVotersPerLocalAuth(); j++) {
			// sleep(1);
			pkeys = loc_auths[i].get_public_keys();
			choix = rand() % prop->get_nbCandidats() + 1;
			clear_clear_votes[choix - 1] += 1;

			vote = pow(M, choix); // Vote: M^mi
			// clear_local_votes.push_back(vote);
			clients.push_back(new Client(j, M, &loc_auths[i]));
			clients.back()->vote(choix);
		}

		// Affichage des votes clairs (test du déchiffrement)
		/*
		std::cout << "Votes clairs sur l'autorité " << i + 1 << " :\n > ";
		cpp_int sum = 0;
		for (size_t i = 0; i < clear_local_votes.size(); i++) {
			std::cout << clear_local_votes[i] << ", ";
			sum += clear_local_votes[i];
		}
		std::cout << "\nTotal: " << sum << " (mod N = " << boost::multiprecision::powm(sum, 1, pkeys[0].N) << ")\n\n";
		clear_local_votes.clear();
		*/
	}
	std::cout << "   \033[1mVotes clairs: \033[0m";
	for (size_t i = 0; i < clear_clear_votes.size(); i++)
		std::cout << i+1 << ": " << clear_clear_votes[i] << " | ";
	std::cout << "\n";
}

void App::filter_local_boards() {
	std::cout << "\033[1;33m ❯ Filtrage des bulletins locaux par timestamp, signature, preuve de vote et preuve d'égalité:\033[0m\n";
	
	for (size_t i = 0; i < loc_auths.size(); i++) {

		Verifier::filter_local_board(loc_auths[i].get_bulletin_board().get_board(), loc_auths[i].get_public_keys());
		
	}
}

void App::compute_local_tallies_and_transmission() {
	std::cout << "\033[1;33m ❯ Décompte des bulletins locaux et publication des résultats sur les boards régionaux:\033[0m\n";
	
	// Tally des sommes locales et cout des tableaux locaux pour vérification
    for (size_t i = 0; i < loc_auths.size(); i++) {
        loc_auths[i].make_tally(loc_auths[i].get_public_key().N);
        // loc_auths[i].cout_board();
    }

    // Transmettre aux régionales
    for (size_t i = 0; i < loc_auths.size(); i++) {
        loc_auths[i].transmit_results();
    }
};

void App::compute_regional_tallies_and_transmission() {
	std::cout << "\033[1;33m ❯ Décompte des bulletins régionaux et publication des résultats sur le board national:\033[0m\n";
	
	// Tally des sommes régionales et cout des tableaux régionaux pour vérification
    for (size_t i = 0; i < reg_auths.size(); i++) {
        reg_auths[i].make_tally(reg_auths[i].get_public_key().N);
        // reg_auths[i].cout_board();
    }

    // Transmettre à la nationale
    for (size_t i = 0; i < reg_auths.size(); i++) {
        reg_auths[i].transmit_results();
    }
};

void App::compute_national_tally() {
	std::cout << "\033[1;33m ❯ Décompte des bulletins nationaux:\033[0m\n";

	// Tally des sommes nationales et cout du tableau national pour vérification
    nat_auth.make_tally(nat_auth.get_public_key().N);
    // nat_auth.cout_board();
};

void App::publish_vote_results() {
	std::cout << "\033[1;33m ❯ Extraction des résultats du vote à partir du décompte total déchiffré:\033[0m\n";

	// Publication des résultats du vote
    nat_auth.transmit_results();
};