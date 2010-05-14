/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : main.cpp
OBJET            : programme principal
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
TODO :
- TODO statistiques pour determiner quelle structure choisir

============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <ctime>

#include "../headers/Generator.h"
#include "../headers/Graph.h"

#define REPERTOIRE "../test/"
#define TEST_GENE_IN "../test/noms.dat"
#define TEST_GENE_OUT "../test/gene"

using namespace std;



int main(int argc, char* argv[]) {

    /* Variables */
    int choice; /* Choix de l'utilisateur */

    string choice2; /* Choix d'affichage du rapport */
    clock_t t_ini, t_open, t_cfc, t_dist, t_create; /* Stockage des temps d'execution */

    string nom_in, nom_out;
    string dir_in, dir_out;
    string opt;
    string repertory;

    Generator gene;
    Graph G;

    // Stockage de l'option' de lancement
    if (argc > 1)
        opt = argv[1];

    if ((argc == 5) && ( (opt == "--log") || (opt == "-l") ) ) {
        /* 1er argument : nom de l'execution
           2eme argument : option (-log)
           3eme argument : nombre de sommets
           4eme argument : densite de relation
           5eme argument : nombre (ou densite, on verra) de questions */
        gene.changeOptionAutomatic( TEST_GENE_IN, TEST_GENE_OUT, atoi(argv[2]),
            (int) atoi(argv[3]), (int) atoi(argv[4]) );
        gene.generateFile();

        repertory = TEST_GENE_OUT;
        G.initGraph(repertory);

        cout << G.getSizeGraph() << " " << atoi(argv[3]) << " " << atoi(argv[4]) << " ";

        /* Calcul des CFC */
        t_ini = clock();
        G.searchSCC();
        t_cfc = clock();

        cout << ((double) t_cfc - t_ini) / CLOCKS_PER_SEC << " ";

        /*Calcul des chemins */
        t_ini = clock();
        G.searchDistances();
        t_dist = clock();

        cout << ((double) t_dist - t_ini) / CLOCKS_PER_SEC << endl;

    } else if ( (argc == 2) && ( (opt == "--help") || (opt == "-h") ) ) {
        cout << endl;
        cout << "	 _                          " << endl;
        cout << "	| |    __ _  __ _  ___ _ __ " << endl;
        cout << "	| |   / _` |/ _` |/ _ \\ '__|" << endl;
        cout << "	| |__| (_| | (_| |  __/ |   " << endl;
        cout << "	|_____\\__,_|\\__, |\\___|_|   " << endl;
        cout << "	            |___/        " << endl << endl;
        cout << "Lager Ain't a Graph Explorer for Rookies !" << endl << endl << endl;

        cout << "USAGE: " << argv[0] << " <OPTION>" << endl;
        cout << endl << "OPTION : " << endl;
        cout << " --log <Nombre_de_sommets> <Nombre_de_relations> <Nombre_de_qestions>"
             << endl << "\t| Lance le programme le plus simplement possible"
             << endl << "\t| Les informations passees en parametre permettent de generer"
             << endl << "\t| un graphe aleatoirement, le graphe genere est ensuite analyse"
             << endl << "\t| par LAGER et les resultats seront affiches sur une seule ligne"
             << endl << "\t| avec le format suivant : "
             << endl << "\t| <Nombre_de_sommet> <Nombre_de_relation>"
             << " <Nombre_de_questions> <Temps_calcul_CFC> <Temps_calcul_questions>"
             << endl << endl;

        cout << " <fichier_d_entree> <fichier_de_sortie>"
             << endl << "\t| Lance LAGER en utilisant le premier argument comme fichier source"
             << endl << "\t| (Le fichier d'entree doit exister)"
             << endl << "\t| Les donnees sont ensuite automatiquement sauvegardees "
             << endl << "\t| dans le fichier indique par le second argument"
             << endl << "\t| (Le fichier de sortie est cree automatiquement s'il n'existe pas)"
             << endl << endl;

        cout << " <fichier_d_entree>"
             << endl << "\t| Lance LAGER en utilisant cet argument comme fichier source"
             << endl << "\t| (Ce fichier doit exister)"
             << endl << "\t| Il sera demande a l'utilisateur le chemin du fichier de sortie"
             << endl << endl;

        cout << " (Aucun argument)"
             << endl << "\t| Lance LAGER normalement"
             << endl << endl;


    } else {
        cout << endl;
        cout << "	 _                          " << endl;
        cout << "	| |    __ _  __ _  ___ _ __ " << endl;
        cout << "	| |   / _` |/ _` |/ _ \\ '__|" << endl;
        cout << "	| |__| (_| | (_| |  __/ |   " << endl;
        cout << "	|_____\\__,_|\\__, |\\___|_|   " << endl;
        cout << "	            |___/        " << endl << endl;
        cout << "Lager Ain't a Graph Explorer for Rookies !" << endl << endl;
        cout << "- Appuyez sur 1 pour charger un graphe" << endl;
        cout << "- Appuyez sur 2 pour analyser un graphe" << endl;
        cout << "- Appuyez sur 3 pour recuperer les donnees de Facebook" << endl;
        cout << "- Appuyez sur 4 pour generer un graphe aleatoire" << endl;
        // cout << "- Appuyez sur 5 pour changer de structure de donnee" << endl;
        cout << "- Appuyez sur 0 pour fermer le programme" << endl << endl;


        while (1) {
            cout << "Entrez votre choix : ";
            cin >> choice;

            switch (choice) {

            case 0 :

                return 0;
                break;

            case 1 :

                if (argc > 1) {
                    /* S'il y a 1 argument, on l'utilise comme nom de fichier d'entree */
                    nom_in = argv[1];
                } else {
                    /* S'il n'y a pas d'argument, on demande à l'utilisateur d'entrer
                       les noms des fichiers d'entree et de sortie */
                    cout << "Entrez le nom du graphe : ";
                    cin >> nom_in;
                    cout << endl;
                }
                dir_in = REPERTOIRE + nom_in;
                /* concaténation du repertoire test avec le nom du fichier d'entree */


                cout << "Lecture du fichier... ";
                t_ini = clock();

                G.initGraph(dir_in);

                t_open = clock();

                cout << ((double) t_open - t_ini) / CLOCKS_PER_SEC << " sec." << endl << endl;
                choice = -1;
                break;

            case 2 :

                if (G.isAnalysable()) {
                    /* graphe enregistre */

                    if (!G.isAnalyzed()) {
                        if (argc > 2) {
                            /* s'il y a 2 arguments, on utilise le 2eme argument comme
                               nom de fichier de sortie */
                            nom_out = argv[2];
                        } else if (argc > 1) {
                            /* s'il n'y a qu'un seul argument, le fichier de sortie
                               sera argv[1].res */
                            nom_out = nom_in;
                            nom_out += ".res";
                        } else {
                            /* s'il n'y a pas d'argument, on demande à l'utilisateur d'entrer
                               le nom du fichier de sortie */
                            cout << "Entrez le nom du fichier resultat : ";
                            cin >> nom_out;
                            cout << endl;
                        }

                        dir_out = REPERTOIRE + nom_out;
                        /* concaténation du repertoire test avec le nom du fichier d'entree */

                        cout << "Recherche des CFC... ";

                        t_ini = clock();

                        G.searchSCC();

                        t_cfc = clock();
                        cout << ((double) t_cfc - t_ini) / CLOCKS_PER_SEC
                        << " sec." << endl;


                        cout << "Recherche des plus courts chemins... ";
                        t_ini = clock();

                        G.searchDistances();

                        t_dist = clock();
                        cout << ((double) t_dist - t_ini) / CLOCKS_PER_SEC
                        << " sec." << endl << endl;

                        G.saveGraph(dir_out);

                        cout << "Donnees sauvegardees... " << endl;
                        G.setAnalyzed(true);
                    } else {
                        cout << "Graphe deja analyse !" << endl << endl;
                    }

                    cout << "Voulez-vous afficher le rapport ? (o/n) ";
                    cin >> choice2;
                    if (choice2 == "o" || choice2 == "O"
                            || choice2 == "oui" || choice2 == "Oui") {
                        G.printGraph();
                    }
                    cout << endl;

                } else {
                    cerr << "Graphe non enregistre !" << endl;
                }
                choice = -1;
                break;

            case 3 :

                cout << "Recuperation des donnees de Facebook... " << "Indisponible."
                << endl << endl;
                choice = -1;

                break;

            case 4 :

                gene.changeOptionManual();

                cout << "Generation d'un fichier... ";
                t_ini = clock();


                gene.generateFile();

                t_create = clock();

                cout << ((double) t_create - t_ini) / CLOCKS_PER_SEC << " sec."
                << endl << endl;
                choice = -1;
                break;
                /*
                            case 5 :

                                cout << "Structure actuellement utilisee : " << typestruct << endl;
                                cout << "Veuillez choisir la nouvelle structure (m pour matrice ou l pour liste)" << endl;
                                typestruct = 'x';
                                while ((typestruct != 'm') && (typestruct != 'l')) {
                                    cin >> typestruct;
                                }
                                cout << endl;
                                choice = -1;
                                break;
                */
            default :

                cout << "Veuillez entrer un chiffre correct." << endl << endl;
                break;

            }

            /* Nettoyage du tampon */
            cin.clear();
            while (cin.get() != '\n') { };
        }
    }

}
