/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Summit.cpp
OBJET            : Structure de sommet
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../headers/Summit.h"

/* PROCEDURE : printSummit - Affichage d'un element de type s_summit */
void printSummit (s_summit s) {
    cout << "Nom : " << s.name << endl;
    cout << "    id( " << s.id << " ) frequence( " << s.freq << " ) " << endl;
    // cout << "    debut( " << s.beg << " ) fin( " << s.end << " ) numero( " << s.num << " )" << endl;
    //cout << "    important ( " << s.important << " )" << endl;
}
/* -------------------------------------------------------------------------- */


/* FONCTION : orderBeg - Donne une notion d'ordre entre deux elements de type s_summit, le critere est l'attribut beg */
bool orderBeg(s_summit a, s_summit b) {
    return (a.beg < b.beg);
}
/* -------------------------------------------------------------------------- */


/* FONCTION : orderEnd - Donne une notion d'ordre entre deux elements de type s_summit, le critere est l'attribut end */
bool orderEnd(s_summit a, s_summit b) {
    return (a.end < b.end);
}
/* -------------------------------------------------------------------------- */

