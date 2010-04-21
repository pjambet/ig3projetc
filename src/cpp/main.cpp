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
#include "../h/matAdj.h"
#include "../h/lscAdj.h"
#include "../h/generate_mat.h"

int main(int argc, char* argv[]) {

    int i, n, m, temp = 0, x = 0, y = 0, **M;
    char *nom_in, *nom_out, dir_in[6] = "test/", dir_out[6] = "test/", *buffer, typestruct;
    liste *L, *P;
    sommet* s, *d;
    FILE* fic_in, *fic_out;

    typestruct = 'm'; // Choix de la structure, m pour matrice, l pour liste
    nom_in = (char*) malloc(16*sizeof(char));
    nom_out = (char*) malloc(16*sizeof(char));

    if (argc > 2) { // s'il y a 2 arguments, on les utilise comme noms de fichiers d'entrée et de sortie
        nom_in = argv[1];
        nom_out = argv[2];
    } else if (argc > 1) { // s'il n'y a qu'un seul argument, le fichier de sortie sera argv[1].res
        nom_in = argv[1];
        strcpy(nom_out, nom_in);
        strcat(nom_out, ".res");
    } else { // s'il n'y a pas d'argument, on demande à l'utilisateur d'entrer les noms des fichiers d'entrée et de sortie
        printf("Entrez le nom du graphe.\n");
        scanf("%s", nom_in);
        printf("Entrez le nom du fichier resultat.\n");
        scanf("%s", nom_out);
        printf("\n");
    }

    strcat(dir_in, nom_in); // concaténation du repertoire test avec le nom du fichier d'entrée
    strcat(dir_out, nom_out); // concaténation du repertoire test avec le nom du fichier de sortie

    fic_in = fopen(dir_in, "r");
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
                //ajoutFin(L, x, y); // creation de la liste d'adjacence L
                //ajoutFin(P, y, x); // creation de la liste duale d'adjacence P
            }
            i++;
        }

        if (typestruct == 'm') { // Matrice

            PPG(M, s, n);
            PPGD(M, s, n);

        } else if (typestruct == 'l') { // Liste

            PPG(L, s, n);
            PPGD(P, s, n);

        }

        fic_out = fopen(dir_out, "w+"); // traiement du fichier resultat
        temp = getNbCFC(s, n); // recuperation du nombre de cfc
        fprintf(fic_out, "%d\n", temp);
        buffer = getCFC(s, n); // recuperation des cfc
        fprintf(fic_out, "%s\n", buffer);

        fscanf(fic_in, "%d\n", &m); // lecture du nombre de sommets du graphe
        i = 0;
        while (i < m) { // lecture des questions
            fscanf(fic_in, "%d -> %d\n", &x, &y);
            algoDijkstra(M, d, n, x);
            y = getIndice(s, n, y);
            buffer = getCheminMin(d, n, y);
            fprintf(fic_out, "%s", buffer);
            i++;
        }

        fclose(fic_in);
        fclose(fic_out);

    } else {
        printf("Lecture du fichier impossible\n");
    }

}
