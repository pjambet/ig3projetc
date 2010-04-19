/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Generator.h
OBJET            : Genere des fichiers de donnee
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

/*=================================
Includes
===================================*/
#include "../h/Generator.h"

/*=================================*/


void generateFile(string dest, int nb_person) {
  srand(time(NULL));

  int i, j;
  int random, ratio;
  char nom[50];
  FILE* fichier;

  int** matrice;
  vector< string > database;

  int nb_link, nb_question;


  /* Initialisation du fichier de noms */
  fichier = fopen(FICHIER_DAT, "r");

  while (!feof(fichier)) {
    fscanf(fichier, "%[^,\t\n\r]\n", nom);
    database.push_back(nom);
  }
  fclose(fichier);

  fichier = fopen(dest.c_str(), "w+");


  /* Nombre de personne */
  fprintf(fichier, "%d\n", nb_person);

  /* Personnes */
  for (i = 0; i < nb_person; i++){
    strcpy(nom, generateName(database).c_str());
    random = rand()%100;
    fprintf(fichier, "%s, %d, %d\n", nom, i, random);
  }

  /* Initialisation de la matrice */
  matrice = (int**) malloc(nb_person*sizeof(int*));
  for (i = 0; i < nb_person; i++){
    matrice[i] = (int*) malloc(nb_person*sizeof(int));
  }

  /* Matrice de relation */
  ratio = RATIO_MIN + rand()%(RATIO_MAX - RATIO_MIN + 1);
  nb_link = generateMatrix(nb_person, matrice, ratio);

  /* Nombre de relation */
  fprintf(fichier, "%d\n", nb_link);

  for (i = 0; i < nb_person; i++){
    for (j = 0; j < nb_person; j++){
      if (matrice[i][j]) {
        fprintf(fichier, "%d, %d\n", i, j);
      }
    }
  }


  /* Matrice de question */
  nb_question = generateMatrix(nb_person, matrice, RATIO_QUESTION);
  fprintf(fichier, "%d\n", nb_question);

  for (i = 0; i < nb_person; i++){
    for (j = 0; j < nb_person; j++){
      if (matrice[i][j] && (i != j)) {
        fprintf(fichier, "%d -> %d\n", i, j);
      }
    }
  }

  for (i = 0; i < nb_person; i++){
    free(matrice[i]);
  }
  free(matrice);
  fclose(fichier);
}

int generateMatrix(int nb, int** m, int r) {
  int i, j;
  int cpt;
  int random;

  cpt = 0;

  for (i = 0; i < nb; i++){
    for (j = 0; j < nb; j++){
      random = rand()%101;
      if (random > r){
        m[i][j] = 0;
      } else {
        m[i][j] = 1;
        cpt++;
      }
    }
  }

  return cpt;
}

string generateName(vector< string > v) {
  int random;

  random = rand()%v.size();
  return v[random];
}
