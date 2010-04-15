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
    int TAILLE_GRAPH;
    char* NOM_GRAPH;
    char NOM_DIR[6] = "test/";

    if (argc > 1) {
        NOM_GRAPH = argv[1];
    } else {
        NOM_GRAPH = (char*) malloc(10*sizeof(char));
        printf("Entrez le nom du graphe.\n");
        scanf("%s", NOM_GRAPH);
        printf("\n");
    }
    strcat(NOM_DIR, NOM_GRAPH);
    strcpy(NOM_GRAPH, NOM_DIR);

    TAILLE_GRAPH = number_nodes(NOM_GRAPH);
    //generate_matrix(TAILLE_GRAPH);
    printf("Matrice d'adjacence :\n");
    matAdjCFC(NOM_GRAPH, TAILLE_GRAPH);
    printf("\nListe d'adjacence :\n");
    lscAdjCFC(NOM_GRAPH, TAILLE_GRAPH);
    //system("PAUSE");
}
