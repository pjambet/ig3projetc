/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : struct_sommet.cpp
OBJET            : Classe pour stocker les donnees d'un sommet
--------------------------------------------------------------------------------
DATE DE CREATION : 29/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */
#include "../h/struct_sommet.h"


bool orderFin(s_sommet a, s_sommet b) {
  return (a.fin < b.fin);
}

bool orderDeb(s_sommet a, s_sommet b) {
  return (a.deb < b.deb);
}

bool orderId(s_sommet a, s_sommet b) {
  return (a.id < b.id);
}
