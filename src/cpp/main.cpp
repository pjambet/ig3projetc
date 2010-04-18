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

    int i, n, m, temp, x = 0, y = 0, **M;
    char *nom_in, *nom_out, dir_in[6] = "test/", dir_out[6] = "test/", *buffer, typestruct;
    liste *L, *P;
    sommet* s;
    FILE* fichier;

    typestruct = 'm'; // Choix de la structure, m pour matrice, l pour liste

    if (argc > 2) { // s'il y a 2 arguments, on les utilise comme noms de fichiers d'entrée et de sortie
        nom_in = argv[1];
        nom_out = argv[2];
    } else if (argc > 1) { // s'il n'y a qu'un seul argument, le fichier de sortie sera argv[1].res
        nom_in = argv[1];
        nom_out = (char*) malloc(16*sizeof(char));
        strcpy(nom_out, nom_in);
        strcat(nom_out, ".res");
    } else { // s'il n'y a pas d'argument, on demande à l'utilisateur d'entrer les noms des fichiers d'entrée et de sortie
        nom_in = (char*) malloc(16*sizeof(char));
        nom_out = (char*) malloc(16*sizeof(char));
        printf("Entrez le nom du graphe.\n");
        scanf("%s", nom_in);
        printf("Entrez le nom du fichier resultat.\n");
        scanf("%s", nom_out);
        printf("\n");
    }

    strcat(dir_in, nom_in); // concaténation du repertoire test avec le nom du fichier d'entrée
    strcat(dir_out, nom_out); // concaténation du repertoire test avec le nom du fichier de sortie

    fichier = fopen(dir_in, "r");
    if (fichier != NULL) { // lecture du graphe

        buffer = (char*) malloc(((3*n)+1)*sizeof(char));
        fgets(buffer, 8, fichier); // lecture du nombre de sommets du graphe
        i = 0;
        n = atoi(buffer);
        s = iniSommet(n);
        M = iniMat(n);
        L = iniListe(n);
        P = iniListe(n);

        while (i < n) { // lecture des id / nom / frequence
            fscanf(fichier, "%[^,], %d, %d\n", buffer, &x, &y);
            strcpy(s[i].nom, buffer);
            s[i].num = i;
            s[i].id = x;
            s[i].freq = y;
            i++;
        }

        fgets(buffer, 8, fichier); // lecture du nombre d'arretes du graphe
        i = 0;
        m = atoi(buffer);
        while (i < m) { // lecture les relations entre les sommets
            fscanf(fichier, "%d, %d\n", &x, &y);
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

        fgets(buffer, 8, fichier); // lecture du nombre de questions
        i = 0;
        m = atoi(buffer);
        while (i < m) { // lecture des questions
            fscanf(fichier, "%d -> %d\n", &x, &y);
            i++;
        }

        fclose(fichier);

        if (typestruct == 'm') { // Matrice

            PPG(M, s, n);
            PPGD(M, s, n);

        } else if (typestruct == 'l') { // Liste

            PPG(L, s, n);
            PPGD(P, s, n);

        }

        fichier = fopen(dir_out, "w+"); // traiement du fichier resultat
        temp = getNbCFC(s, n); // recuperation du nombre de cfc
        fprintf(fichier, "%d\n", temp);
        buffer = getCFC(s, n); // recuperation des cfc
        fprintf(fichier, "%s\n", buffer);
        fclose(fichier);

        algoDijkstra(M, s, n, x);


    } else {
        printf("Lecture du fichier impossible\n");
    }

}
