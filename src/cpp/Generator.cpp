/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Generator.h
OBJET            : Genere des fichiers de donnee
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../h/Generator.h"

/*=================================
Constantes
===================================*/
#define RATIO_MIN 10
#define RATIO_MAX 50

#define RATIO_QUESTION 100


void generateFile(string source, string dest, int nb_person) {
  srand(time(NULL));

  int i, j;
  int random, ratio;
  char nom[50];
  int id;

  FILE* fichier;
  FILE* fichier_questions;

  int** matrice;
  vector< string > database_nom;
  vector< int > database_id;

  int nb_link, nb_question;
  vector< int > liste_id;


  /* Initialisation du fichier de noms */
  fichier = fopen(source.c_str(), "r");

  while (!feof(fichier)) {
    fscanf(fichier, "%[^,\t\n\r], %d\n", nom, &id);
    database_nom.push_back(nom);
    database_id.push_back(id);
  }

  fclose(fichier);


  fichier = fopen(dest.c_str(), "w+");

  /* Nombre de personne */
  fprintf(fichier, "%d\n", nb_person);

  /* Personnes */
  i = 0;
  while (i < nb_person){
    random = rand()%database_nom.size();
    strcpy(nom, database_nom[random].c_str());
    id = database_id[random];

    if (find(liste_id.begin(), liste_id.end(), id) == liste_id.end()) {
      /* Teste si la personne est déjà dans la liste */
    random = rand()%100;
    fprintf(fichier, "%s, %d, %d\n", nom, id, random);

    liste_id.push_back(id); /* Je stocke les id choisies */
    i++;
    }
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
      if ((matrice[i][j])) {
        fprintf(fichier, "%d, %d\n", liste_id[i], liste_id[j]);
      }
    }
  }


  /* Matrice de question */

  /*
  nb_question = generateMatrix(nb_person, matrice, RATIO_QUESTION);
  fprintf(fichier, "%d\n", nb_question);
  fprintf(fichier_questions, "%d\n", nb_question);

  for (i = 0; i < nb_person; i++){
    for (j = 0; j < nb_person; j++){
      if (matrice[i][j]) {
        fprintf(fichier, "%d -> %d\n", liste_id[i], liste_id[j]);
        fprintf(fichier_questions, "%d -> %d\n", liste_id[i], liste_id[j]);
      }
    }
  }
  */

  nb_question = nb_person - 1;
    fprintf(fichier, "%d\n", nb_question);

  random = rand()%nb_person;
    /* On choisit une id au hasard dans la liste */


  for (i = 0; i < nb_person; i++){
    if (i != random) {
        fprintf(fichier, "%d -> %d\n", liste_id[random], liste_id[i]);
    }
  }
  /* On se pose les questions random -> "tous les autres" */


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

  for (i = 0; i < nb; i++) {
    if (m[i][i]) {
      m[i][i] = 0;
      cpt--;
    }
  }

  return cpt;
}
