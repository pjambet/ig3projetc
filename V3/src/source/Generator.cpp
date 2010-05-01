/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Generator.h
OBJET            : Genere des fichiers de donnee
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */
#include "../headers/Generator.h"

/*=================================
Constantes
===================================*/
#define FREQ_MAX 100
#define RATIO 10000


void generateFile(string source, string dest, int n, int d_rel, int d_quest) {
  srand(time(NULL));

  /* Variables */
  int i, j;
  int random;
  char nom[50];
  int id;

  FILE* fichier;

  int** matrice;
  vector< string > database_nom;
  vector< int > database_id;

  int nb_link, nb_question;
  vector< int > liste_id;


  /* Initialisation du fichier de noms */
  fichier = fopen(source.c_str(), "r");

  while (!feof(fichier)) {
    fscanf(fichier, "%[^,\n], %d\n", nom, &id);
    database_nom.push_back(nom);
    database_id.push_back(id);
  }

  fclose(fichier);
    assert(n < (int) database_nom.size());
      /* On verifie que le nombre de personne est bien inferieur au nombre de personne dans la database */


  fichier = fopen(dest.c_str(), "w+");

  /* Nombre de personne */
  fprintf(fichier, "%d\n", n);

  /* Personnes */
  i = 0;
  while (i < n){
    random = rand()%database_nom.size();
    strcpy(nom, database_nom[random].c_str());
    id = database_id[random];

    if (find(liste_id.begin(), liste_id.end(), id) == liste_id.end()) {
      /* Si la personne n'est pas encore dans la liste */

      random = rand()%FREQ_MAX;
        /* Determination de la frequence au hasard */
      fprintf(fichier, "%s, %d, %d\n", nom, id, random);
      liste_id.push_back(id);
        /* Stockage des id choisies */
      i++;

    }
  }


  /* Initialisation de la matrice */
  matrice = (int**) malloc(n*sizeof(int*));
  for (i = 0; i < n; i++){
    matrice[i] = (int*) malloc(n*sizeof(int));
  }


  /* Matrice de relation */
  nb_link = generateMatrix(n, matrice, d_rel);

  /* Nombre de relation */
  fprintf(fichier, "%d\n", nb_link);

  for (i = 0; i < n; i++){
    for (j = 0; j < n; j++){
      if ((matrice[i][j])) {
        fprintf(fichier, "%d, %d\n", liste_id[i], liste_id[j]);
      }
    }
  }


  /* Matrice de question */
  nb_question = generateMatrix(n, matrice, d_quest);

  /* Nombre de question */
  fprintf(fichier, "%d\n", nb_question);

  for (i = 0; i < n; i++){
    for (j = 0; j < n; j++){
      if (matrice[i][j]) {
        fprintf(fichier, "%d -> %d\n", liste_id[i], liste_id[j]);
      }
    }
  }


  /* Liberation de la memoire*/
  for (i = 0; i < n; i++){
    free(matrice[i]);
  }
  free(matrice);
  fclose(fichier);
}

int generateMatrix(int n, int** m, int r) {
  int i, j;
  int cpt;
  int random;

  cpt = 0;

  for (i = 0; i < n; i++){
    for (j = 0; j < n; j++){
      random = rand()%(RATIO+1);
      if ( (random >= r) || (i == j) ){
        m[i][j] = 0;
      } else {
        m[i][j] = 1;
        cpt++;
      }
    }
  }

  return cpt;
}
