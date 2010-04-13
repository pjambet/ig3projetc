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

int main(int argc, char* argv[]) {
    matAdjCFC(argv[1]); //matAdjCFC("./test/graph.txt");

    return 0;
}
