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

    int i, n, m, x = 0, y = 0, **M;
    char *nom_in, *nom_out, dir_in[6] = "test/", dir_out[6] = "test/", typestruct, *buffer;
    liste *L, *P;
    sommet* s;
    FILE* fichier;

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

    strcat(dir_in, nom_in);
    strcat(dir_out, nom_out);

    printf("Choix de la structure (m ou l) :\n");
    while ((typestruct != 'm') && (typestruct != 'l')) {
        scanf("%c", &typestruct);
    }

    fichier = fopen(dir_in, "r");
    if (fichier != NULL) { // lecture du graphe

        buffer = (char*) malloc(((3*n)+1)*sizeof(char));
        fgets(buffer, 8, fichier); // lecture du nombre de sommets du graphe
        i = 0;
        n = atoi(buffer);
        s = iniSommet(n);
        M = iniMat(n);

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
            fscanf(fichier, "%d, %d", &x, &y);
            x = getIndice(s, n, x);
            y = getIndice(s, n, y);
            M[y][x] = 1;
            i++;
        }

        fgets(buffer, 8, fichier); // lecture du nombre de questions
        i = 0;
        m = atoi(buffer);
        fgetc(fichier);
        while (i < m) { // lecture des questions
            fscanf(fichier, "%d -> %d", &x, &y);
            // TODO : Traitement des questions
        }

        fclose(fichier);

        if (typestruct == 'm') { // Matrice

            PPG(M, s, n);
            triDecroissant(s, n);
            PPGD(M, s, n);

        } else { // Liste

            PPG(L, s, n);
            triDecroissant(s, n);
            PPGD(P, s, n);

        }

        fichier = fopen(dir_out, "w+");
        m = getNbCFC(s, n); // recuperation du nombre de cfc
        fprintf(fichier, "%d\n", m);
        buffer = getCFC(s, n); // recuperation des cfc
        fprintf(fichier, "%s\n", buffer);
        fclose(fichier);

    } else {
        printf("Lecture du fichier impossible\n");
    }

}

    /*L = (liste*) malloc(n*sizeof(liste));
    for (i = 0; i < n; i++) {
        L[i] = NULL;
    }

    P = (liste*) malloc(n*sizeof(liste));
    for (i = 0; i < n; i++) {
        P[i] = NULL;
    }

    if (atoi(&c)) { // Ajout à la fin de l[j] de i
        liste p = (liste) malloc(sizeof(cell));
        liste pd = (liste) malloc(sizeof(cell));
        p->val = i;
        pd->val = j;
        p->suiv = NULL;
        pd->suiv = NULL;
        if (l[j] == NULL) {
            l[j] = p;
        } else {
            liste temp = l[j];
            while (temp->suiv != NULL) {
                temp = temp->suiv;
            }
            temp->suiv = p;
        }
        if (ld[i] == NULL) {
            ld[i] = pd;
        } else {
            liste temp = ld[i];
            while (temp->suiv != NULL) {
                temp = temp->suiv;
            }
            temp->suiv = pd;
        }
    }
    i++;*/
