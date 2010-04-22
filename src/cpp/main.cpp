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

    int i, n, m, temp, x, y, t_ini, t_fin, **M, choix, *tabQ;
    bool continuer = true;
    char *nom_in, *nom_out, *buffer, typestruct, dir_in[6] = "test/", dir_out[6] = "test/";
    liste *L, *P;
    sommet* s, *d;
    FILE* fic_in, *fic_out;

    typestruct = 'm'; // Choix de la structure, m pour matrice, l pour liste

    cout << "                                              " << endl;
    cout << "     ____            _      _                 " << endl;
    cout << "    |  _ \\ _ __ ___ (_) ___| |_    ___        " << endl;
    cout << "    | |_) | '__/ _ \\| |/ _ \\ __|  / __|       " << endl;
    cout << "    |  __/| | | (_) | |  __/ |_  | (__        " << endl;
    cout << "    |_|   |_|  \\___// |\\___|\\__|  \\___|       " << endl;
    cout << "                   |__/                       " << endl;
    cout << "                                              " << endl;
    cout << "                                              " << endl;
    cout << "- Appuyez sur 1 pour charger un graphe" << endl;
    cout << "- Appuyez sur 2 pour analyser un graphe" << endl;
    cout << "- Appuyez sur 3 pour generer un graphe aleatoire" << endl;
    cout << "- Appuyez sur 0 pour fermer le programme" << endl << endl;

    while (continuer) {

        cout << "Entrez votre choix." << endl;
        cin >> choix;

        switch (choix) {

            case 0 :

                return 0;
                break;

            case 1 :

                t_ini = GetTickCount();
                nom_in = (char*) malloc(16*sizeof(char));
                if (argc > 1) { // s'il y a 1 argument, on l'utilise comme nom de fichier d'entrée
                    nom_in = argv[1];
                } else { // s'il n'y a pas d'argument, on demande à l'utilisateur d'entrer les noms des fichiers d'entrée et de sortie
                    printf("Entrez le nom du graphe.\n");
                    scanf("%s", nom_in);
                    printf("\n");
                }

                strcat(dir_in, nom_in); // concaténation du repertoire test avec le nom du fichier d'entrée

                fic_in = fopen(dir_in, "r"); // ouverture de "test/nom_in"

                if (fic_in != NULL) { // lecture du graphe

                    fscanf(fic_in, "%d\n", &n); // lecture du nombre de sommets du graphe
                    i = 0;
                    s = iniSommet(n);
                    d = iniSommet(n);
                    M = iniMat(n);
                    L = iniListe(n);
                    P = iniListe(n);
                    buffer = (char*) malloc(1000*sizeof(char));

                    while (i < n) { // lecture des id / nom / frequence
                        fscanf(fic_in, "%[^,], %d, %d\n", buffer, &x, &y);
                        strcpy(s[i].nom, buffer);
                        s[i].num = i;
                        s[i].id = x;
                        s[i].freq = y;
                        d[i].id = x;
                        d[i].freq = y;
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
                    printf("Lecture du fichier impossible\n");
                }

                t_fin = GetTickCount() - t_ini;
                cout << "(Temps d'execution : " << t_fin << "ms)" << endl << endl;
                break;

            case 2 :

                t_ini = GetTickCount();
                nom_out = (char*) malloc(16*sizeof(char));
                if (argc > 2) { // s'il y a 2 arguments, on utilise le 2eme argument comme nom de fichier de sortie
                    nom_out = argv[2];
                } else if (argc > 1) { // s'il n'y a qu'un seul argument, le fichier de sortie sera argv[1].res
                    strcpy(nom_out, nom_in);
                    strcat(nom_out, ".res");
                } else { // s'il n'y a pas d'argument, on demande à l'utilisateur d'entrer le nom du fichier de sortie
                    printf("Entrez le nom du fichier resultat.\n");
                    scanf("%s", nom_out);
                    printf("\n");
                }

                strcat(dir_out, nom_out); // concaténation du repertoire test avec le nom du fichier de sortie

                fic_out = fopen(dir_out, "w+"); // création de "test/nom_out"

                if (typestruct == 'm') { // Matrice

                    PPG(M, s, n); // création de la structure sommet s pour recupérer le nombre de cfc et les cfc
                    PPGD(M, s, n);

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
                            algoDijkstra(M, d, n, x); // création de la structure sommet d pour récupérer les temps d'accès du sommet x aux autres sommets
                        }
                        y = tabQ[i];
                        i++;
                        y = getIndice(s, n, y);
                        buffer = getCheminMin(d, n, y); // récupération du t_min et du chemin de x à y
                        fprintf(fic_out, "%s", buffer);
                    }

                } else if (typestruct == 'l') { // Liste

                    PPG(L, s, n); // création de la structure sommet s pour recupérer le nombre de cfc et les cfc
                    PPG(P, s, n);

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
                            algoDijkstra(L, d, n, x); // création de la structure sommet d pour récupérer les temps d'accès du sommet x aux autres sommets
                        }
                        y = tabQ[i];
                        i++;
                        y = getIndice(s, n, y);
                        buffer = getCheminMin(d, n, y); // récupération du t_min et du chemin de x à y
                        fprintf(fic_out, "%s", buffer);
                    }

                }

                fclose(fic_out); // fermeture de "test/nom_out"

                t_fin = GetTickCount() - t_ini;
                cout << "(Temps d'execution : " << t_fin << "ms)" << endl << endl;
                break;

            case 3 :

                cout << "Entrez le nombre de sommets desire" << endl;
                cin >> i;
                t_ini = GetTickCount();
                generateFile("test/noms.dat", "test/gene", i);
                t_fin = GetTickCount() - t_ini;
                cout << "(Temps d'execution : " << t_fin << "ms)" << endl << endl;
                break;

        }

    }

}
