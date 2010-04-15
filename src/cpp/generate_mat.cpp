/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : generate_mat.cpp
OBJET            : matrice adjacente
--------------------------------------------------------------------------------
DATE DE CREATION : 13/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../h/generate_mat.h"

void generate_matrix(int x){
  srand(time(NULL));

  int random;
  int i, j;
  FILE* file_mat;

  file_mat = fopen("test/matrix", "w+"); // Chemin à changer

  /* On genere aleatoirement des 0 et des 1, puis on les met dans le fichier */
  for (i = 0; i < x; i++){
    for (j = 0; j < x; j++){
      random = rand()%101;
      // On fait un random pour avoir 80% de 0 et 20% de 1
      if (random < 80){
        fputc('0', file_mat);
      } else {
        fputc('1', file_mat);
      }
    }
    if (i != (x - 1)){
      fputc('\n', file_mat);
    } // On va a la ligne sauf a la derniere ligne
  }

  fclose(file_mat);
}


int number_nodes(char* fileName){
  int node_cpt;
  FILE* file_mat;
  char c;

  file_mat = fopen(fileName, "r");
  node_cpt = 0;

  c = fgetc(file_mat);
  while (c != '\n'){
    node_cpt++;
    c = fgetc(file_mat);
  }

  fclose(file_mat);
  return node_cpt;
}

