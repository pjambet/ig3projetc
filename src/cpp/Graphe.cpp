/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Graphe.h
OBJET            : Structure de graphe
--------------------------------------------------------------------------------
DATE DE CREATION : 27/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

#include "../h/Graphe.h"

/*=================================
Constructeurs et Desctructeurs
===================================*/
Graphe::Graphe(): nbCFC(0), nbDist(0) {
}

Graphe::~Graphe() {
}


/*=================================
Resolution
===================================*/
void Graphe::resolution(UserData* u) {
  clear();

  vector <s_sommet>* tabSommetTemp;
  MatAdj M;
  ListeVoisins L;


  if ((*u).get_structFriends() == 'm') { // Matrice
    M.iniMat(u);
    M.PPG(u);
    //M.PPGD();
    tabSommetTemp = M.recupTabSommet();

  } else if ((*u).get_structFriends() == 'l') { // Liste
    L.iniList(u);
    L.PPG(u);
    // L.PPGD();
    tabSommetTemp = L.recupTabSommet();

  }

  loadCFC(tabSommetTemp);

  delete tabSommetTemp;
  //free(tabSommetTemp);
}

void Graphe::loadCFC(vector<s_sommet>* tabSommet) {
  int d, f; /* Repères de debut et fin d'intervalle */
  unsigned int i;
  int cpt_CFC; /* Compteur de CFC*/
  vector <int > v;

  d = (*tabSommet)[0].deb;
  f = (*tabSommet)[0].fin;
  cpt_CFC = 0;

  if ((*tabSommet).size() != 0) {
    cpt_CFC++;
    listCFC.push_back(v);
    listCFC[cpt_CFC-1].push_back((*tabSommet)[0].id);
    for (i = 1; i < (*tabSommet).size(); i++) {
      /* On regarde les autres sommets */
        if ((d < ((*tabSommet)[i].deb)) && (f > ((*tabSommet)[i].fin))) {
          listCFC[cpt_CFC-1].push_back((*tabSommet)[i].id);
        } else {
            d = (*tabSommet)[i].deb;
            f = (*tabSommet)[i].fin;
            cpt_CFC++;
            listCFC.push_back(v);
            listCFC[cpt_CFC-1].push_back((*tabSommet)[i].id);
        }
    }
  }

  nbCFC = cpt_CFC;

}


void Graphe::saveGraphe(string fileName) {
  FILE* f_out;
  unsigned int i, j;
  string choice;

  f_out = fopen(fileName.c_str(), "w+");

  /* Nombre de CFC */
  fprintf(f_out, "%d\n", nbCFC);

  /* CFC */
  for (i = 0; i < listCFC.size(); i++) {
    for (j = 0; j < listCFC[i].size()-1; j++) {
      fprintf(f_out, "%d, ", listCFC[i][j]);
    }
    fprintf(f_out, "%d\n", listCFC[i].back());
  }

  fclose(f_out);

/*
  cout << "Fichier enregistre, voulez-vous afficher le rapport ? (o/n) ";
  cin >> choice;
  if (choice == "o" || choice == "O") {
    print();
  }*/
}

/*=================================
Autres
===================================*/
void Graphe::print() {
  unsigned int i, j;
  cout << "Rapport de graphe :" << endl << endl;
  cout << "Nombre de CFC : " << nbCFC << endl;
  cout << "CFC : " << endl;

  for (i = 0; i < listCFC.size(); i++) {
    cout << "{ ";
    for (j = 0; j < listCFC[i].size(); j++) {
      cout << listCFC[i][j] << " ";
    }
    cout << "}" << endl;
  }

}

void Graphe::clear() {
  nbCFC = 0;
  nbDist = 0;
  listCFC.clear();
  listDist.clear();
}
