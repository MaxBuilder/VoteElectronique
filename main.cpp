#define _CRT_SECURE_NO_DEPRECATE

#include "src/App.hpp"

int main(int argc, char const *argv[])
{
    bool verbose = false;
    bool random_votes = true;
    if (argc > 1 && ((!strcmp(argv[1], "--verbose")) || (!strcmp(argv[1], "-v"))) ) {
        verbose = true;
    }

    if (argc > 2 && (!strcmp(argv[2], "--votes")) ) {
        random_votes = false;
    }


    // Instanciation de l'autorité nationale et lecture du fichier de configuration
    App *app = App::getApp();

    // Instanciation des autorités régionales et locales
    app->instanciate_authorities(verbose);

    if (random_votes) {
        // Génération de votes aléatoires chiffrés dans les boards des autorités locales
        srand(clock());
        app->generate_random_votes();
    }
    else {
        app->read_vote_file();
    }

    // Filtrage des bulletins locaux par timestamp, signature, preuve de vote et preuve d'égalité
    app->filter_local_boards();

    // Décompte des bulletins locaux et publication des résultats sur les boards régionaux
    app->compute_local_tallies_and_transmission(verbose);

    // Décompte des bulletins régionaux et publication des résultats sur le board national
    app->compute_regional_tallies_and_transmission(verbose);

    // Décompte des bulletins nationaux
    app->compute_national_tally(verbose);

    // Extraction des résultats du vote à partir du décompte total déchiffré
    app->publish_vote_results();

    return 0;
}
