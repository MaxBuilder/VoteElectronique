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

void App::instanciate_authorities(bool verbose) {
	Properties *prop = Properties::getProperties();

	std::cout << "\033[1;33m ❯ Génération des autorités régionales:\033[0m\n";
	// Génération des autorités régionales
	for (int i = 0; i < prop->get_nbRegionalAuth(); i++) {
		reg_auths.push_back(RegionalAuthority(i + 1, nat_auth, verbose));
	}
	std::cout << "	✅ " << prop->get_nbRegionalAuth() << " paires de clés "<<prop->get_keySize()<<" bits ont été générées\n";

	std::cout << "\033[1;33m ❯ Génération des autorités locales:\033[0m\n";
	// Génération des autorités locales
	for (size_t i = 0; i < reg_auths.size(); i++) {
		for (int j = 0; j < prop->get_nbLocalPerRegionalAuth(); j++) {
			loc_auths.push_back(LocalAuthority(j + 1, reg_auths[i], verbose));
		}
	}
	std::cout << "	✅ " << prop->get_nbRegionalAuth()*prop->get_nbLocalPerRegionalAuth() << " paires de clés "<<prop->get_keySize()<<" bits ont été générées\n";
	std::cout << "\n";
}

CryptoUtils::SKeyRSA App::generateVoterKeys()
{
    boost::random_device rn1;
    boost::random_device rn2;
    boost::random_device rn3;

    boost::random::mt11213b base_gen(rn1);
    boost::random::independent_bits_engine<boost::random::mt11213b, BITSIZE, cpp_int> gen(base_gen);

    boost::random::mt19937 gen2(rn2);

    cpp_int p;
    while (true)
    {
        p = gen();
        if (powm(p, 1, 2) == 0)
            continue;
        if (miller_rabin_test(p, 25, gen2))
            break;
    }

    cpp_int q;
    while (true)
    {
        q = gen();
        if (powm(q, 1, 2) == 0 || q == p)
            continue;
        if (miller_rabin_test(q, 25, gen2))
            break;
    }

    cpp_int N;
    multiply(N, p, q);

    cpp_int phi_N, e;
    multiply(phi_N, cpp_int(p - 1), cpp_int(q - 1));

    e = CryptoUtils::getRandomInversibleElement(phi_N);

    cpp_int d = boost::integer::mod_inverse(e, phi_N);
    CryptoUtils::SKeyRSA sk;
    sk.pkey.e = e;
    sk.pkey.n = N;
    sk.d = d;
    sk.p = p;
    sk.q = q;

    return sk;
}

cpp_int App::signRSA(cpp_int message, CryptoUtils::SKeyRSA sk)
{
    cpp_int sign;

    cpp_int hash = CryptoUtils::sha256(boost::to_string(message));
    sign = powm(hash, sk.d, sk.pkey.n);
    return sign;
}

EncryptedVote App::vote(std::array<PublicKey, 3> pkeys, cpp_int M, int vote)
{
	CryptoUtils::SKeyRSA voterKeys;
	voterKeys = generateVoterKeys();

    cpp_int M_pow_vote = boost::multiprecision::pow(M, vote); // Vote: M^mi

	EncryptedVote ev;
	ev.pkey = voterKeys.pkey;

    // Création du vote local
    CipherStruct locVote = Encryption::encrypt(pkeys[0], M_pow_vote);
    cpp_int locSign = signRSA(locVote.cipher, voterKeys);
	// ToDo : Legal vote proof
    ev.localVote = {locVote.cipher, locSign, cpp_int(0)}; 

    // Création du vote régional
    CipherStruct regVote = Encryption::encrypt(pkeys[1], M_pow_vote);
    cpp_int regSign = signRSA(regVote.cipher, voterKeys);
    ev.regionalVote = {regVote.cipher, regSign, cpp_int(0)};

    // Création du vote national
    CipherStruct natVote = Encryption::encrypt(pkeys[2], M_pow_vote);
    cpp_int natSign = signRSA(natVote.cipher, voterKeys);
    ev.nationalVote = {natVote.cipher, natSign, cpp_int(0)};

    // Génération de la preuve d'égalité des votes (zero-knowledge proof 3)
    ev.eq_proof = Prover::generate_equality_proof(M_pow_vote, std::array<CipherStruct, 3>{locVote, regVote, natVote}, pkeys, Verifier::get_challenge());

	return ev;
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


	EncryptedVote ev;
	// Générations de votes aléatoires
	for (size_t i = 0; i < loc_auths.size(); i++) {
		for (int j = 0; j < prop->get_nbVotersPerLocalAuth(); j++) {
			// sleep(1);
			pkeys = loc_auths[i].get_public_keys();
			choix = rand() % prop->get_nbCandidats() + 1;
			clear_clear_votes[choix - 1] += 1;

			// Génération d'un vote par la méthode client
			ev = App::vote(loc_auths[i].get_public_keys(), M, choix);
			// Ajout du bulletin au BulletinBoard
			loc_auths[i].get_bulletin_board().get_board().push_back(
				new LocalBulletin(j, ev.pkey, time(nullptr), 
				ev.localVote, ev.regionalVote, ev.nationalVote, ev.eq_proof));
		}
	}
	std::cout << "	\033[1mVotes clairs: \033[0m";
	for (size_t i = 0; i < clear_clear_votes.size(); i++)
		std::cout << i+1 << ": " << clear_clear_votes[i] << " | ";
	std::cout << "\n";
}



void App::read_vote_file() {
	std::cout << "\033[1;33m ❯ Génération de votes issus de la configuration dans les boards des autorités locales:\033[0m\n";

	// Lecture et parsing du fichier de configuration
	// using Json = nlohmann::json;
	// std::ifstream ifs("votes.json");
	// Json jf = Json::parse(ifs);
	// TODO : fixer la lecture du fichier

	std::vector<std::array<int, 5>> votes;
	votes.push_back({1, 1, 1, 0, 0});
	votes.push_back({2, 2, 2, 1, 0}); // fraud 
    votes.push_back({1, 1, 1, 0, 0});
    votes.push_back({2, 2, 1, 0, 0}); // fraud
    votes.push_back({1, 1, 1, 0, 0});
    votes.push_back({2, 2, 2, 0, 0});
	votes.push_back({2, 2, 2, 0, 0});
    votes.push_back({2, 2, 2, 0, 0});
    votes.push_back({2, 2, 2, 1, 0}); // fraud
    votes.push_back({3, 3, 3, 0, 0});
    votes.push_back({3, 3, 3, 0, 0});
    votes.push_back({2, 1, 2, 0, 0}); // fraud
    votes.push_back({3, 3, 3, 0, 0});
    votes.push_back({3, 3, 3, 0, 0});
    votes.push_back({3, 3, 3, 0, 1}); // fraud
    votes.push_back({3, 3, 3, 0, 0});
	nb_voters = votes.size();

	std::array<PublicKey, 3> pkeys;
	cpp_int M_pow_vote;
	int loci;
	int counter = 1;
	EncryptedVote ev;
	CryptoUtils::SKeyRSA voterKeys;
	std::time_t timestamp;
	CipherStruct locVote, regVote, natVote;
	cpp_int locSign, regSign, natSign;
	
	for (std::array<int, 5> v : votes) {

		loci = rand() % loc_auths.size();
		pkeys = loc_auths[loci].get_public_keys();

		// Fausse signature ?
		if (v[4]) {
			voterKeys.pkey.e = cpp_int(3);
			voterKeys.pkey.n = cpp_int(2);
		}
		else {
			voterKeys = generateVoterKeys();
		}
		ev.pkey = voterKeys.pkey;

		// Vote local
		M_pow_vote = boost::multiprecision::pow(M, v[0]);
		locVote = Encryption::encrypt(pkeys[0], M_pow_vote);
		if (v[4])	locSign = cpp_int(0);
		else		locSign = signRSA(locVote.cipher, voterKeys);
		ev.localVote = {locVote.cipher, locSign, cpp_int(0)};

		// Vote regional
		M_pow_vote = boost::multiprecision::pow(M, v[1]);
		regVote = Encryption::encrypt(pkeys[1], M_pow_vote);
		if (v[4])	regSign = cpp_int(0);
		else		regSign = signRSA(regVote.cipher, voterKeys);
		ev.regionalVote = {regVote.cipher, regSign, cpp_int(0)};


		// Vote national
		M_pow_vote = boost::multiprecision::pow(M, v[2]);
		natVote = Encryption::encrypt(pkeys[2], M_pow_vote);
		if (v[4])	natSign = cpp_int(0);
		else		natSign = signRSA(natVote.cipher, voterKeys);
		ev.nationalVote = {natVote.cipher, natSign, cpp_int(0)};

		// Génération de la preuve d'égalité des votes (zero-knowledge proof 3)
    	ev.eq_proof = Prover::generate_equality_proof(M_pow_vote, std::array<CipherStruct, 3>{locVote, regVote, natVote}, pkeys, Verifier::get_challenge());

		// Faux timestamp ?
		if (v[3]) {
			timestamp = time(nullptr) + 9999999;
		}
		else {
			timestamp = time(nullptr) + rand() % 1000;
		}

		// Ajout du bulletin au BulletinBoard
		loc_auths[loci].get_bulletin_board().get_board().push_back(
			new LocalBulletin(counter, ev.pkey, timestamp, 
			ev.localVote, ev.regionalVote, ev.nationalVote, ev.eq_proof));
		
		counter++;
	}
}


void App::filter_local_boards() {
	std::cout << "\033[1;33m ❯ Filtrage des bulletins locaux par timestamp, signature, preuve de vote et preuve d'égalité:\033[0m\n";
	int total_fraud = 0;
	for (size_t i = 0; i < loc_auths.size(); i++) {
		total_fraud += Verifier::filter_local_board(loc_auths[i].get_bulletin_board().get_board(), loc_auths[i].get_public_keys());
	}
	std::cout << "	✅ " << total_fraud << " bulletins frauduleux ont été supprimés. " << nb_voters-total_fraud << " bulletins valides restants.\n";
}

void App::compute_local_tallies_and_transmission(bool verbose) {
	std::cout << "\033[1;33m ❯ Décompte des bulletins locaux et publication des résultats sur les boards régionaux\033[0m\n";
	if (verbose)
		std::cout << "\n";
	
	// Tally des sommes locales et cout des tableaux locaux pour vérification
    for (size_t i = 0; i < loc_auths.size(); i++) {
        loc_auths[i].make_tally();
		if (verbose)
        	loc_auths[i].cout_board();
    }

    // Transmettre aux régionales
    for (size_t i = 0; i < loc_auths.size(); i++) {
        loc_auths[i].transmit_results();
    }
};

void App::compute_regional_tallies_and_transmission(bool verbose) {
	std::cout << "\033[1;33m ❯ Décompte des bulletins régionaux et publication des résultats sur le board national:\033[0m\n";
	if (verbose)
		std::cout << "\n";

	// Tally des sommes régionales et cout des tableaux régionaux pour vérification
    for (size_t i = 0; i < reg_auths.size(); i++) {
        if (reg_auths[i].make_tally()) {
			if (verbose)
				reg_auths[i].cout_board();
			std::cout << "	✅ Résultats déchiffrés de Régionale n°" << i+1 << " conformes à la somme des décomptes clairs reçus des locales.\n\n";       
		}
		else
            std::cout << "❌\n";
    }

    // Transmettre à la nationale
    for (size_t i = 0; i < reg_auths.size(); i++) {
        reg_auths[i].transmit_results();
    }
};

void App::compute_national_tally(bool verbose) {
	std::cout << "\033[1;33m ❯ Décompte des bulletins nationaux:\033[0m\n";
	if (verbose)
		std::cout << "\n";

	// Tally des sommes nationales et cout du tableau national pour vérification
    if (nat_auth.make_tally()) {
		if (verbose)
			nat_auth.cout_board();
		std::cout << "	✅ Les résultats déchiffrés de l'autorité nationale sont conformes à la somme des décomptes clairs reçus de ses régionales.\n\n";       
	}
	else
		std::cout << "❌\n";
};

void App::publish_vote_results() {
	std::cout << "\033[1;33m ❯ Extraction des résultats du vote à partir du décompte total déchiffré:\033[0m\n";

	// Publication des résultats du vote
    nat_auth.transmit_results();
};