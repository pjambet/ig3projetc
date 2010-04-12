/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : lsc.h
OBJET            : liste simplement chainée
--------------------------------------------------------------------------------
DATE DE CREATION : 12/04/2010
AUTEUR           : Pierre JAMBET
--------------------------------------------------------------------------------

============================================================================= */



typedef struct cell
{
  struct cell* suiv;
  int val;

} cell_s;

typedef cell* LSC;

LSC creerListe();
void supprListe();
