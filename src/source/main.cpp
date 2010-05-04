/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : main.cpp
OBJET            : programme principal
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
TODO :
- Gerer quand l'utilisateur entre autre chose qu'un entier au menu
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
    time_t t_ini, t_open, t_cfc, t_dist, t_create; /* Stockage des temps d'execution */

    string nom_in, nom_out;
    string dir_in, dir_out;

    Graph G;

    cout << "                                              " << endl;
    cout << "     ____            _      _                 " << endl;
    cout << "    |  _ \\ _ __ ___ (_) ___| |_    ___        " << endl;
    cout << "    | |_) | '__/ _ \\| |/ _ \\ __|  / __|       " << endl;
    cout << "    |  __/| | | (_) | |  __/ |_  | (__        " << endl;
    cout << "    |_|   |_|  \\___// |\\___|\\__|  \\___|      " << endl;
    cout << "                   |__/                       " << endl;
    cout << "                                              " << endl;
    cout << "                                              " << endl;
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
                  /* S'il n'y a pas d'argument, on demande à l'utilisateur d'entrer les noms des fichiers d'entree et de sortie */
                    cout << "Entrez le nom du graphe : ";
                    cin >> nom_in;
                    cout << endl;
                }
                dir_in = REPERTOIRE + nom_in;
                  /* concaténation du repertoire test avec le nom du fichier d'entree */

                t_ini = clock();
                cout << "Lecture du fichier... ";

                G.initGraph(dir_in);

                t_open = clock();
                cout << ((double) t_open - t_ini) / CLOCKS_PER_SEC << " sec." << endl << endl;
                choice = -1;
                break;

            case 2 :

                if (G.isAnalysable()) {
                  /* graphe enregistre */

                    if (argc > 2) {
                      /* s'il y a 2 arguments, on utilise le 2eme argument comme nom de fichier de sortie */
                        nom_out = argv[2];
                    } else if (argc > 1) {
                      /* s'il n'y a qu'un seul argument, le fichier de sortie sera argv[1].res */
                        nom_out = nom_in;
                        nom_out += ".res";
                    } else {
                      /* s'il n'y a pas d'argument, on demande à l'utilisateur d'entrer le nom du fichier de sortie */
                        cout << "Entrez le nom du fichier resultat : ";
                        cin >> nom_out;
                        cout << endl;
                    }
                    dir_out = REPERTOIRE + nom_out;
                      /* concaténation du repertoire test avec le nom du fichier d'entree */

                    t_ini = clock();
                    cout << "Recherche des CFC... ";

                    G.searchCFC();

                    t_cfc = clock();
                    cout << ((double) t_cfc - t_ini) / CLOCKS_PER_SEC << " sec." << endl;


                    t_ini = clock();
                    cout << "Recherche des plus courts chemins... ";

                    G.searchDistances();

                    t_dist = clock();
                    cout << ((double) t_dist - t_ini) / CLOCKS_PER_SEC << " sec." << endl << endl;

                    G.saveGraph(dir_out);

                    cout << "Donnees sauvegardees... " << endl;
                    cout << "Voulez-vous afficher le rapport ? (o/n) ";
                    cin >> choice2;
                    if (choice2 == "o" || choice2 == "O" || choice2 == "oui" || choice2 == "Oui") {
                        G.printGraph();
                    }
                    cout << endl;

                } else {
                    cerr << "Graphe non enregistre !" << endl;
                }
                choice = -1;
                break;

            case 3 :

                cout << "Recuperation des donnees de Facebook... " << "Indisponible." << endl << endl;
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

                t_ini = clock();
                cout << "Generation d'un fichier... ";

                generateFile(TEST_GENE_IN, TEST_GENE_OUT, nbPerson, (int) (densite_relation*100), (int) (densite_question));

                t_create = clock();
                cout << ((double) t_create - t_ini) / CLOCKS_PER_SEC << " sec." << endl << endl;
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
