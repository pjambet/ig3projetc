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


/*=================================
Includes
===================================*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <ctime>

#include "../headers/Generator.h"
#include "../headers/Graph.h"

/*=================================
Constantes
===================================*/
#define REPERTOIRE "../test/"
#define TEST_GENE_IN "../test/noms.dat"
#define TEST_GENE_OUT "../test/gene"

using namespace std;


int main(int argc, char* argv[]) {

    /* VARIABLES */
    int choice;
    string choice2;
		/* - choice : choix de l'utilisateur pour le menu
		   - choice2 : choix de l'utilisateur pour les questions (o/n) */

    clock_t t_ini, t_open, t_cfc, t_dist, t_create;
		/* Stockage des temps d'execution */

    string nom_in, nom_out;
    string dir_in, dir_out;
		/* Noms des fichiers d'entree et de sortie */

    string opt;
    string repertory;
		/* Stocke le premier argument s'il y en a un */

    Generator gene;
		/* Variable pour generer des fichiers d'entree */

    Graph G;
		/* Variable pour analyser les fichiers d'entree */
    char GStruct;

    /* ****************************************************** */
    /* ****************************************************** */


	/* S'il existe un premier argument, on le stocke pour plus tard */
    if (argc > 1)
        opt = argv[1];

	/* Mode de test activable avec l'option --log ou -l */
    if ( (opt == "--log") || (opt == "-l") ) {
		if (argc == 6) {
        /* 1er argument : nom de l'executable
           2eme argument : option (--log ou -l)
           3eme argument : nombre de sommets
           4eme argument : nombre de relations
           5eme argument : nombre de questions
           6eme argument : structure pour l'analyse */

        gene.changeOptionAutomatic( TEST_GENE_IN, TEST_GENE_OUT, atoi(argv[2]),
            (int) atoi(argv[3]), (int) atoi(argv[4]) );
        gene.generateFile();

        G.setStructGraph(argv[5][0]);
        repertory = TEST_GENE_OUT;
        G.initGraph(repertory);

        cout << G.getSizeGraph() << "\t" << atoi(argv[3]) << "\t" << atoi(argv[4]) << "\t";

        /* Calcul des CFC */
        t_ini = clock();
        G.searchSCC();
        t_cfc = clock();

        cout << ((double) t_cfc - t_ini) / CLOCKS_PER_SEC << "\t";

        /* Calcul des chemins */
        t_ini = clock();
        G.searchDistances();
        t_dist = clock();

        cout << ((double) t_dist - t_ini) / CLOCKS_PER_SEC << endl;

		} else {
        cout << " MODE TEST USAGE : --log <Nombre_de_sommets> <Nombre_de_relations> <Nombre_de_qestions> <structure (m/l)>" << endl;

		}

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
        cout << " --log <Nombre_de_sommets> <Nombre_de_relations> <Nombre_de_qestions> <structure (m/l)>"
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
        cout << "- Appuyez sur 5 pour changer la structure" << endl;
        cout << "- Appuyez sur 0 pour fermer le programme" << endl << endl;


        while (1) {
            cout << "Entrez votre choix : ";
            cin >> choice;

            switch (choice) {


			/* CASE 0 : Arret du programme */
            case 0 :

                return 0;
                break;
			/* -------------------------------------------------------------- */


			/* CASE 1 : Ouverture d'un fichier de donnee */
            case 1 :

                if (argc > 1) {
					/* Si le premier argument donne en premier parametre n'est pas --log
					   On le considere comme le fichier d'entree */
                    nom_in = argv[1];

                } else {
                    /* S'il n'y a pas d'argument, on demande à l'utilisateur d'entrer
                       les noms des fichiers d'entree */
                    cout << "Entrez le nom du graphe : ";
                    cin >> nom_in;
                    cout << endl;

                }

                dir_in = REPERTOIRE + nom_in;
                /* concaténation du repertoire test avec le nom du fichier d'entree */

                cout << "Lecture du fichier (structure ";

                GStruct = G.getStructGraph();
                switch (GStruct) {
                    case 'm' :
                        cout << "matrice)... ";
                        break;
                    case 'l' :
                        cout << "liste)... ";
                        break;
                    default :
                        cerr << "ERREUR - Structure inconnue. (main.cpp - case 1)";
                        break;
                }

                t_ini = clock();
                G.initGraph(dir_in);
                t_open = clock();

                cout << ((double) t_open - t_ini) / CLOCKS_PER_SEC << " sec." << endl << endl;

                choice = -1;
                break;
			/* -------------------------------------------------------------- */


			/* CASE 2 : Analyse du graphe */
            case 2 :

                if (G.isAnalysable()) {
					/* On teste si un graphe a ete donne en entree */

                    if (!G.isAnalyzed()) {
                        if (argc > 2) {
                            /* s'il y a 2 arguments, on utilise le 2eme argument comme
                               nom de fichier de sortie */
                            nom_out = argv[2];

                        } else if (argc > 1) {
                            /* s'il n'y a qu'un seul argument, le fichier de sortie
                               sera argv[1].res */
                            nom_out = nom_in + ".res";

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

                        cout << ((double) t_cfc - t_ini) / CLOCKS_PER_SEC << " sec." << endl;


                        cout << "Recherche des plus courts chemins... ";

                        t_ini = clock();
                        G.searchDistances();
                        t_dist = clock();

                        cout << ((double) t_dist - t_ini) / CLOCKS_PER_SEC << " sec." << endl << endl;


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
			/* -------------------------------------------------------------- */


			/* CASE 3 : Recuperation de donnees Facebook */
            case 3 :

                cout << "Recuperation des donnees de Facebook... " << endl << endl;
                gene.generateDatabase();

                choice = -1;
                break;
			/* -------------------------------------------------------------- */


			/* CASE 4 : Generation d'un fichier d'entree */
            case 4 :

                gene.changeOptionManual();

                cout << "Generation d'un fichier... ";

                t_ini = clock();
                gene.generateFile();
                t_create = clock();

                cout << ((double) t_create - t_ini) / CLOCKS_PER_SEC << " sec." << endl << endl;

                choice = -1;
                break;
			/* -------------------------------------------------------------- */

			/* CASE 5 : Changement de structure */
            case 5 :

                GStruct = G.getStructGraph();

                cout << "La structure actuelle est ";
                switch (GStruct) {
                    case 'm' :
                        cout << "matrice." << endl;
                        break;
                    case 'l' :
                        cout << "liste." << endl;
                        break;
                    default :
                        cerr << "ERREUR - Structure inconnue. (main.cpp - case 5)" << endl;
                        break;
                }

                cout << "Changer de structure ? (o/n) ";
                cin >> choice2;

                if (choice2 == "o" || choice2 == "O"
                    || choice2 == "oui" || choice2 == "Oui") {
                    switch (GStruct) {
                    case 'm' :
                        G.setStructGraph('l');
                        break;
                    case 'l' :
                        G.setStructGraph('m');
                        break;
                    default :
                        cerr << "ERREUR - Structure inconnue. (main.cpp - case 5)" << endl;
                        break;
                    }
                }
                cout << endl;
                break;
			/* -------------------------------------------------------------- */

			/* DEFAULT : Autres cas */
            default :

                cout << "Veuillez entrer un chiffre correct." << endl << endl;
                break;

            }

            /* Nettoyage du tampon si le choix donne est incorrect */
            cin.clear();
            while (cin.get() != '\n') { };
        }
    }

}
