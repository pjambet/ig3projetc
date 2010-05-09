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
    int nbPerson;
    float densite_relation, densite_question;
    string choice2; /* Choix d'affichage du rapport */
    clock_t t_ini, t_open, t_cfc, t_dist, t_create; /* Stockage des temps d'execution */

    string nom_in, nom_out;
    string dir_in, dir_out;
    string opt;
    string repertory;

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
        generateFile( TEST_GENE_IN, TEST_GENE_OUT, atoi(argv[2]),
                      (int) (atoi(argv[3])*100), convertNumToRatio(atoi(argv[4]), atoi(argv[2]) ) );
        repertory = TEST_GENE_OUT;
        G.initGraph(repertory);

        /* Calcul des CFC */
        t_ini = clock();
        cout << G.getSizeGraph() << " " << atoi(argv[3]) << " " << atoi(argv[4]) << " ";
        G.searchSCC();

        t_cfc = clock();

        cout << ((double) t_cfc - t_ini) / CLOCKS_PER_SEC << " ";

        /*Calcul des chemins */
        t_ini = clock();

        G.searchDistances();

        t_dist = clock();

        cout << ((double) t_dist - t_ini) / CLOCKS_PER_SEC << endl;

    } else if ( (argc == 2) && ( (opt == "--help") || (opt == "-h") ) ) {
        cout << "Usage: " << argv[0] << " <OPTION>" << endl;
        cout << endl << "OPTION : " << endl;
        cout << "\t--log <nb_sommetq> <densite_relation> <nb_qestions>"
        << endl << "\tLance le programme le plus simplement possible"
        << endl << "\tLes informations passees en parametre permettent de generer"
        << endl << "\tun graphe aleatoirement, le graphe genere est ensuite analyse"
        << endl << "\tpar LAGER et les resultats seront affiches sur une seule ligne"
        << endl << "\tavec le format suivant : "
        << endl << endl << "<Nombre_de_sommet> <Densite_de_relation>"
        << " <Nombre_de_questions> <temps_calcul_CFC> <temps_calcul_questions>"
        << endl << endl;
    } else {

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

                nbPerson = 0;
                densite_relation = 0;
                densite_question = 0;

                cout << "Entrez le nombre de sommets desires : ";
                cin >> nbPerson;

                cout << "Entrez la densite de relation desiree (ratio pour 100) : ";
                cin >> densite_relation;

                cout << "Entrez la densite de question desiree (ratio pour 100) : ";
                cin >> densite_question;


                cout << "Generation d'un fichier... ";
                t_ini = clock();

                generateFile( TEST_GENE_IN, TEST_GENE_OUT, nbPerson, (int)
                              (densite_relation*100), (int) (densite_question*100) );

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
