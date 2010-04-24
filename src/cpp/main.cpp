/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : main.cpp
OBJET            : programme principal
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <windows.h>
#include "../h/matAdj.h"
#include "../h/lscAdj.h"
#include "../h/generate_mat.h"
#include "../h/Generator.h"

using namespace std;

int main(int argc, char* argv[]) {

    int i, n, m, temp, x, y, **M, choix, *tabQ;
    float t_ini, t_fin;
    char *buffer, typestruct;
    string nom_in, nom_out, dir_in, dir_out;
    liste *L, *P;
    sommet* s;
    FILE* fic_in, *fic_out;

    typestruct = 'm'; // Choix de la structure, m pour matrice, l pour liste

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
    cout << "- Appuyez sur 3 pour generer un graphe aleatoire" << endl;
    cout << "- Appuyez sur 0 pour fermer le programme" << endl << endl;

    while (1) {

        cout << "Entrez votre choix." << endl;
        cin >> choix;

        switch (choix) {

            case 0 :

                return 0;
                break;

            case 1 :

                if (argc > 1) { // s'il y a 1 argument, on l'utilise comme nom de fichier d'entrée
                    nom_in = argv[1];
                } else { // s'il n'y a pas d'argument, on demande à l'utilisateur d'entrer les noms des fichiers d'entrée et de sortie
                    cout << "Entrez le nom du graphe." << endl;
                    cin >> nom_in;
                    cout << endl;
                }
                t_ini = GetTickCount();

                dir_in = "test/" + nom_in; // concaténation du repertoire test avec le nom du fichier d'entrée

                fic_in = fopen(dir_in.c_str(), "r"); // ouverture de "test/nom_in"

                if (fic_in != NULL) { // lecture du graphe

                    fscanf(fic_in, "%d\n", &n); // lecture du nombre de sommets du graphe
                    i = 0;
                    s = iniSommet(n);
                    M = iniMat(n);
                    L = iniListe(n);
                    P = iniListe(n);
                    buffer = (char*) malloc(1000*sizeof(char));

                    while (i < n) { // lecture des id / nom / frequence
                        fscanf(fic_in, "%[^,], %d, %d\n", buffer, &x, &y);
                        strcpy(s[i].nom, buffer);
                        iniEtatSommet(s, n);
                        s[i].num = i;
                        s[i].id = x;
                        s[i].freq = y;
                        i++;
                    }

                    fscanf(fic_in, "%d\n", &m); // lecture du nombre de sommets du graphe
                    i = 0;
                    while (i < m) { // lecture les relations entre les sommets
                        fscanf(fic_in, "%d, %d\n", &x, &y);
                        x = getIndice(s, n, x);
                        y = getIndice(s, n, y);
                        if (typestruct == 'm') {
                            M[x][y] = 1; // remplissage de la matrice d'adjacence M
                        } else if (typestruct == 'l') {
                            ajoutFin(L, x, y); // creation de la liste d'adjacence L
                            ajoutFin(P, y, x); // creation de la liste duale d'adjacence P
                        }
                        i++;
                    }

                    fscanf(fic_in, "%d\n", &m); // lecture du nombre de sommets du graphe
                    i = 0;
                    tabQ = (int*) malloc (2*m*sizeof(int)); // enregistrement des questions dans un tableau
                    while (i/2 < m) { // lecture des questions
                        fscanf(fic_in, "%d -> %d\n", &x, &y);
                        tabQ[i] = x; // les i paires contiennent la source (x) de la question
                        i++;
                        tabQ[i] = y; // les i impaires contiennent la destination (y) de la question
                        i++;
                    }

                    fclose(fic_in); // fermeture de "test/nom_in"

                } else {
                    cerr << "Lecture du fichier impossible" << endl;
                }

                t_fin = (GetTickCount() - t_ini) / 1000;
                cout << "(Temps d'execution : " << t_fin << " sec)" << endl << endl;
                break;

            case 2 :

                if (argc > 2) { // s'il y a 2 arguments, on utilise le 2eme argument comme nom de fichier de sortie
                    nom_out = argv[2];
                } else if (argc > 1) { // s'il n'y a qu'un seul argument, le fichier de sortie sera argv[1].res
                    nom_out = nom_in;
                    nom_out += ".res";
                } else { // s'il n'y a pas d'argument, on demande à l'utilisateur d'entrer le nom du fichier de sortie
                    cout << "Entrez le nom du fichier resultat." << endl;
                    cin >> nom_out;
                    cout << endl;
                }
                t_ini = GetTickCount();

                dir_out = "test/" + nom_out; // concaténation du repertoire test avec le nom du fichier de sortie

                fic_out = fopen(dir_out.c_str(), "w+"); // création de "test/nom_out"

                if (typestruct == 'm') { // Matrice

                    DepthFirstSearch(M, s, n); // Premier DFS de M
                    DepthFirstSearch(M, s, n); // Deuxième DFS de M transposé

                    temp = getNbCFC(s, n); // recuperation du nombre de cfc
                    fprintf(fic_out, "%d\n", temp);
                    buffer = getCFC(s, n); // recuperation des cfc
                    fprintf(fic_out, "%s\n", buffer);

                    i = 0;
                    while (i/2 < m) {
                        x = tabQ[i];
                        i++;
                        if (x != temp) {
                            temp = x;
                            ShortestPath(M, s, n, x); // modification de la structure sommet s pour récupérer les temps d'accès du sommet x aux autres sommets
                        }
                        y = tabQ[i];
                        i++;
                        y = getIndice(s, n, y);
                        buffer = getCheminMin(s, n, y); // récupération du t_min et du chemin de x à y
                        fprintf(fic_out, "%s", buffer);
                    }

                } else if (typestruct == 'l') { // Liste

                    DepthFirstSearch(L, s, n); // Premier DFS de L
                    DepthFirstSearch(P, s, n); // Deuxième DFS de L transposé (P)

                    temp = getNbCFC(s, n); // récuperation du nombre de cfc
                    fprintf(fic_out, "%d\n", temp);
                    buffer = getCFC(s, n); // récuperation des cfc
                    fprintf(fic_out, "%s\n", buffer);

                    i = 0;
                    while (i/2 < m) {
                        x = tabQ[i];
                        i++;
                        if (x != temp) {
                            temp = x;
                            ShortestPath(L, s, n, x); // création de la structure sommet d pour récupérer les temps d'accès du sommet x aux autres sommets
                        }
                        y = tabQ[i];
                        i++;
                        y = getIndice(s, n, y);
                        buffer = getCheminMin(s, n, y); // récupération du t_min et du chemin de x à y
                        fprintf(fic_out, "%s", buffer);
                    }

                }

                fclose(fic_out); // fermeture de "test/nom_out"

                t_fin = (GetTickCount() - t_ini) / 1000;
                cout << "(Temps d'execution : " << t_fin << " sec)" << endl << endl;
                break;

            case 3 :

                cout << "Entrez le nombre de sommets desire" << endl;
                cin >> i;
                t_ini = GetTickCount();
                generateFile("test/noms.dat", "test/gene", i);
                t_fin = (GetTickCount() - t_ini) / 1000;
                cout << "(Temps d'execution : " << t_fin << " sec)" << endl << endl;
                break;

            default :

                cout << "Veuillez entrer un chiffre correct." << endl << endl;
                break;

        }

    }

}
