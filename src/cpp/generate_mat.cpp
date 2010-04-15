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
#define RATIO_MIN 10
#define RATIO_MAX 40

void generate_matrix(int x){
  srand(time(NULL));

  int random;
  int ratio;
  int i, j;
  FILE* file_mat;

  file_mat = fopen("test/matrix", "w+");

  /* Generation aleatoire de 0 et de 1 */
  // 1 - Determiner le taux de nombre de 1 dans la matrice (entre RATIO_MIN et RATIO_MAX)
  ratio = RATIO_MIN + rand()%(RATIO_MAX - RATIO_MIN + 1);

  // 2 - Remplir la matrice avec ce taux de remplissage
  for (i = 0; i < x; i++){
    for (j = 0; j < x; j++){
      random = rand()%101;
      if (random > ratio){
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

