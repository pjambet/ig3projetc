/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : UserData.cpp
OBJET            : Classe pour stocker les donnees d'une fichier utilisateur
--------------------------------------------------------------------------------
DATE DE CREATION : 19/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------

============================================================================= */

/*=================================
Includes
===================================*/
#include "../h/UserData.h"

/*=================================*/


/*=================================
Constructeurs et Desctructeurs
===================================*/
UserData::UserData(string fileName) {
  /* Variables */
    /* Generales */
    int i;
    FILE* filedata;

    /* Etape 2 */
    Person pers;
      char pers_name[50];
      int pers_id = 0;
      int pers_freq = 0;

    /* Etape 4 */
    int x, y;
    map<int, Person>::iterator it1;

    /* Etape 6 */
    map<int, vector<int> >::iterator it2;



  /* Corps de la fonction */
  filedata = fopen(fileName.c_str(), "r");

  if (filedata == NULL) {
    cerr << "Erreur - Impossible d'ouvrir le fichier ou fichier inexistant." << endl;
    exit (-1);
  } else {

    /* Etape 1 - Lecture du nombre de personne*/
    fscanf(filedata, "%d\n", &nb_person);

    /* Etape 2 - Lecture des personnes*/
    for (i = 0; i < nb_person; i++) {
      fscanf(filedata, "%[^,], %d, %d\n", pers_name, &pers_id, &pers_freq);

      pers.set_name(pers_name);
      pers.set_id(pers_id);
      pers.set_freq(pers_freq);

      addPerson(pers);
    }
    /* Etape 3 - Lecture du nombre de relation */
    fscanf(filedata, "%d\n", &nb_link);


    /* Etape 4 - "Remplir la matrice" */
      /* On va lire la liste et stocker progressivement les données */
      for (i = 0; i < nb_link; i++){
        fscanf(filedata, "%d, %d\n", &x, &y);

        it1 = listPerson.find(x);
        (*it1).second.addFriend(y);
       }

       /* Tri de tous les amis */
      for (it1 = listPerson.begin() ; it1 != listPerson.end(); it1++) {
        (*it1).second.sortFriends();
      }

    /* Etape 5 - Lecture du nombre de question */
    fscanf(filedata, "%d\n", &nb_question);

    /* Etape 6 - Stockage des questions */
    for (i = 0; i < nb_question; i++){
      fscanf(filedata, "%d -> %d\n", &x, &y);
      addQuestion(x, y);
    }

    for (it2 = listQuestion.begin() ; it2 != listQuestion.end(); it2++) {
        sort( (*it2).second.begin(), (*it2).second.end() );
    }
  }
}

UserData::~UserData() {
}

/*=================================*/


/*=================================
Accesseurs en ecriture
===================================*/
void UserData::addPerson(Person p) {
  map<int, Person>::iterator it;

  it = listPerson.find(p.get_id());

  if (it != listPerson.end()) {
    /* Si l'id est deja utilise en tant que cle */
    cerr << "Erreur - Redondance d'identifiant : " << p.get_id() << endl;
  } else {
    listPerson[p.get_id()] = p;
  }
}

void UserData::addQuestion(int id1, int id2) {
    listQuestion[id1].push_back(id2);
}

/*=================================*/


/*=================================
Accesseurs en lecture
===================================*/
map < int, Person > UserData::get_listPerson() {
  return listPerson;
}

map < int, vector<int> > UserData::get_listQuestion() {
  return listQuestion;
}

/*=================================*/


/*=================================
Autres et optionnels
===================================*/
bool UserData::is_link(int id1, int id2) {
  map< int, Person >::iterator it;
  vector< int > v;
  int i;
  bool link;

  link = false;
  i = 0;
  it = listPerson.find(id1);
  v = (*it).second.get_listLink();

  if (listPerson.find(id1) == listPerson.end()) {
    /* Si l'id n'est pas dans la liste */
    cerr << "Erreur - Identifiant introuvable : " << id1 << endl;
    exit (-1);
  } else {
    while ((v[i] < id2) && (i < v.size())) {
      i++;
    }

    if (i == v.size()) {
      link = false;
    } else if (v[i] == id2){
      link = true;
    }
  }

  return link;
}

bool UserData::is_question(int id1, int id2) {
  map< int, vector<int> >::iterator it;
  vector< int > v;
  bool question;
  int i;

  question = false;
  i = 0;

  if (listQuestion.find(id1) == listQuestion.end()) {
    /* Si l'id n'est pas dans la liste */
    cerr << "Erreur - Identifiant introuvable : " << id1 << endl;
    exit (-1);
  } else {

    v = listQuestion[id1];
    while ((v[i] < id2) && (i < v.size())) {
      i++;
    }

    if (i == v.size()) {
      question = false;
    } else if (v[i] == id2){
      question = true;
    }
  }
  return question;
}

void UserData::display() {
  map< int, Person >::iterator it1;
  map< int, vector<int> >::iterator it2;
  int i;

  cout << "Liste des personnes :" << endl;

  for (it1 = listPerson.begin() ; it1 != listPerson.end(); it1++) {
    (*it1).second.display();
  }

  cout << endl << "Liste des questions : " << endl;
  for (it2 = listQuestion.begin() ; it2 != listQuestion.end(); it2++) {
    for (i = 0; i < (*it2).second.size(); i++) {
      cout << (*it2).first << " -> " << (*it2).second[i] << endl;
    }
  }
}

/*=================================*/
