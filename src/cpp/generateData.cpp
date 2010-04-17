/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : generate_data.h
OBJET            : Genere des fichiers de donnee (fait a l'arrache)
--------------------------------------------------------------------------------
DATE DE CREATION : 17/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "generateData.h"

#define RATIO_MIN 10
#define RATIO_MAX 50

void generate_data(int nb_person) {
  srand(time(NULL));

  int i, j;
  int random, random2;
  FILE* fichier;

  char r_name[20];

  fichier = fopen("data.txt", "w+");

  /* Nombre de personne */
  fprintf(fichier, "%d\n", nb_person);

  /* Liste des personnes */
  for (i = 0; i < nb_person; i++) {
    random = rand()%100;
    generer_nom_aleatoire(r_name);
    fprintf(fichier, "%s, %d, %d\n", r_name, i, random);
  }

  int** matrice;
  int ratio;
  int nb_link = 0;

  matrice = (int**) malloc(nb_person*sizeof(int*));
  for (i = 0; i < nb_person; i++){
    matrice[i] = (int*) malloc(nb_person*sizeof(int));
  }

  /* Generation aleatoire de 0 et de 1 */
  // 1 - Determiner le taux de nombre de 1 dans la matrice (entre RATIO_MIN et RATIO_MAX)
  ratio = RATIO_MIN + rand()%(RATIO_MAX - RATIO_MIN + 1);

  // 2 - Remplir la matrice avec ce taux de remplissage
  for (i = 0; i < nb_person; i++){
    for (j = 0; j < nb_person; j++){
      random = rand()%101;
      if (random > ratio){
        matrice[i][j] = 0;
      } else {
        matrice[i][j] = 1;
        nb_link++;
      }
    }
  }

  /* Nombre de relation */
  fprintf(fichier, "%d\n", nb_link);

  /* Creation des relations */
  for (i = 0; i < nb_person; i++){
    for(j = 0; j < nb_person; j++){
      if (matrice[i][j]){
        fprintf(fichier, "%d, %d\n", i, j);
      }
    }
  }

  for (i = 0; i < nb_person; i++){
    free(matrice[i]);
  }
  free(matrice);
  fclose(fichier);
}

void generer_nom_aleatoire(char n[20]) {
    int i;
    int nb_lettre;
    int random;
    /*
    for(i = 0; i < 19; i++) {
      n[i] = ' ';
    }*/

    n[19] = '\0';

    nb_lettre = 0;
    while (nb_lettre < 10){
      nb_lettre = rand()%19;
    }

    i = 0;
    while (i < nb_lettre) {
      random = rand()%26;
      switch (random) {
        case 0 : { n[i] = 'a'; break; }
        case 1 : { n[i] = 'b'; break; }
        case 2 : { n[i] = 'c'; break; }
        case 3 : { n[i] = 'd'; break; }
        case 4 : { n[i] = 'e'; break; }
        case 5 : { n[i] = 'f'; break; }
        case 6 : { n[i] = 'g'; break; }
        case 7 : { n[i] = 'h'; break; }
        case 8 : { n[i] = 'i'; break; }
        case 9 : { n[i] = 'j'; break; }
        case 10 : { n[i] = 'k'; break; }
        case 11 : { n[i] = 'l'; break; }
        case 12 : { n[i] = 'm'; break; }
        case 13 : { n[i] = 'n'; break; }
        case 14 : { n[i] = 'o'; break; }
        case 15 : { n[i] = 'p'; break; }
        case 16 : { n[i] = 'q'; break; }
        case 17 : { n[i] = 'r'; break; }
        case 18 : { n[i] = 's'; break; }
        case 19 : { n[i] = 't'; break; }
        case 20 : { n[i] = 'u'; break; }
        case 21 : { n[i] = 'v'; break; }
        case 22 : { n[i] = 'w'; break; }
        case 23 : { n[i] = 'x'; break; }
        case 24 : { n[i] = 'y'; break; }
        case 25 : { n[i] = 'z'; break; }
        default : { i--; }
      }

      i++;
    }

    n[i] = '\0';

}
