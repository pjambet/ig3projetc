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
#include <windows.h>

#include "../h/Generator.h"
#include "../h/UserData.h"
#include "../h/Graphe.h"

#define REPERTOIRE "test/"

using namespace std;

int main(int argc, char* argv[]) {
    /* Variables */
    int choice; /* Choix de l'utilisateur */
    float t_ini, t_fin; /* Stockage des temps d'execution */

    string nom_in, nom_out;
    string dir_in, dir_out;

      /* Case 1 : */
      UserData D;

      /* Case 2 : */
      Graphe G;

      /* Case 4 : */
      int nbPerson;
      int densite_relation, densite_question;


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

                t_ini = GetTickCount();
                  D.openData(dir_in);
                t_fin = (GetTickCount() - t_ini) / 1000;

                 //D.print();
                cout << "(Temps d'execution : " << t_fin << " sec)" << endl << endl;
                break;

            case 2 :
                if (D.is_analysable()) {
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

                    t_ini = GetTickCount();
                    G.resolution(&D);
                    G.saveGraphe(nom_out);

/*                   i = 0;
                    while (i/2 < nbQuest) {
                        x = tabQuest[i];
                        i++;
                        if (x != temp) { // Check pour eviter de refaire un meme ShortestPath
                            temp = x;
                            if (typestruct == 'm') // Matrice
                                ShortestPath(M, s, nbSommet, x); // modification de la structure sommet s pour récupérer les temps d'accès du sommet x aux autres sommets
                            else if (typestruct == 'l')
                                ShortestPath(L, s, nbSommet, x); // création de la structure sommet d pour récupérer les temps d'accès du sommet x aux autres sommets
                        }
                        y = tabQuest[i];
                        i++;
                        y = getIndice(s, nbSommet, y);
                        buffer = getCheminMin(s, nbSommet, y); // récupération du t_min et du chemin de x à y
                        fprintf(fic_out, "%s", buffer);
                    }*/

                    t_fin = (GetTickCount() - t_ini) / 1000;
                    cout << "(Temps d'execution : " << t_fin << " sec)" << endl << endl;

                } else {
                    cerr << "Graphe non enregistre !" << endl;
                }
                break;

            case 3 :

                break;

            case 4 :

                cout << "Entrez le nombre de sommets desires : ";
                cin >> nbPerson;

                cout << "Entrez la densite de question desiree (ratio pour 10 000) : ";
                cin >> densite_relation;

                cout << "Entrez la densite de question desiree (ratio pour 10 000) : ";
                cin >> densite_question;

                t_ini = GetTickCount();
                generateFile("test/noms.dat", "test/gene.txt", nbPerson, densite_relation, densite_question);
                t_fin = (GetTickCount() - t_ini) / 1000;

                cout << "(Temps d'execution : " << t_fin << " sec)" << endl << endl;
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
                break;
*/
            default :

                cout << "Veuillez entrer un chiffre correct." << endl << endl;
                break;

        }

    }

}
