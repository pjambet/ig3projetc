/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : struct_sommet.h
OBJET            : Classe pour stocker les donnees d'un sommet
--------------------------------------------------------------------------------
DATE DE CREATION : 29/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */
#include <iostream>
#include <string>

using namespace std;


typedef struct struct_sommet s_sommet;
struct struct_sommet {

    string nom;
    int id;
    int freq;

    int etat; // -1 = Non atteint, 0 = Atteint, 1 = Exploré
    int deb;
    int fin;
    int num;

    bool important;

};


bool orderFin(s_sommet a, s_sommet b);

bool orderDeb(s_sommet a, s_sommet b);

bool orderId(s_sommet a, s_sommet b);
