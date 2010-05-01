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
UserData::UserData() : analysable(false), nbPerson(0), nbLink(0), nbQuestion(0) {
  matFriends = (int**) malloc (nbPerson*sizeof(int*));
}

UserData::~UserData() {
  int i;


    for (i = 0; i < nbPerson; i++) {
      free(matFriends[i]);
    }
    free(matFriends);
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
    exit (-1);
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

map < int, Friends > UserData::get_listFriends() {
  return listFriends;
}

int** UserData::get_matFriends() {
  return matFriends;
}

map < int, vector<int> > UserData::get_listQuestion() {
  return listQuestion;
}

Person UserData::get_Person(int id) {
  map<int, Person>::iterator it;

  it = listPerson.find(id);


  if (it != listPerson.end()) {
    /* Si l'id est deja utilise en tant que cle */
    cerr << "Erreur - Id inexistant : " << id << endl;
    exit (-1);
  }

  return listPerson[id];
}

int UserData::get_nbPerson() {
  return nbPerson;
}

int UserData::get_nbLink() {
  return nbLink;
}

int UserData::get_nbQuestion() {
  return nbQuestion;
}

char UserData::get_structFriends() {
  return structFriends;
}

int UserData::get_idToRank(int id){
  return idToRank[id];
}

int UserData::get_rankToId(int rank){
  return rankToId[rank];
}
/*=================================*/


/*=================================
Autres et optionnels
===================================*/
void UserData::openData(string fileName) {
  clear();

  /* Variables */
    /* Generales */
    int i, j;
    FILE* filedata;

    /* Etape 2 */
    Person pers;
      char pers_name[50];
      int pers_id = 0;
      int pers_freq = 0;

    /* Etape 4 */
    int x, y;
    map<int, Person>::iterator itPers;
    map<int, Friends>:: iterator itFrie;

    /* Etape 6 */
    map<int, vector<int> >::iterator itQuest;


  /* Corps de la fonction */
  filedata = fopen(fileName.c_str(), "r");

  if (filedata == NULL) {
    cerr << "Erreur - Impossible d'ouvrir le fichier ou fichier inexistant." << endl;
    exit (-1);
  } else {

    /* Etape 1 - Lecture du nombre de personne*/
    fscanf(filedata, "%d\n", &nbPerson);

    /* Etape 2 - Lecture des personnes*/
    for (i = 0; i < nbPerson; i++) {
      fscanf(filedata, "%[^,], %d, %d\n", pers_name, &pers_id, &pers_freq);

      pers.set_name(pers_name);
      pers.set_id(pers_id);
      pers.set_freq(pers_freq);

      addPerson(pers);
    }

    /* Etape 3 - Lecture du nombre de relation */
    fscanf(filedata, "%d\n", &nbLink);

    /* Etape intermediaire : Definition de la structure a adopter */
    structFriends = defineStructFriends();

    /* Etape 4 - Stocker les amis en fonction de la structure choisie */
    if (structFriends == 'm') {
      /* Initialisation de la matrice */
      matFriends = (int**) malloc (nbPerson*sizeof(int*));
        for (i = 0; i < nbPerson; i++) {
          matFriends[i] = (int*) malloc (nbPerson*sizeof(int));
        }

      for (i = 0; i < nbPerson; i++) {
        for (j = 0; j < nbPerson; j++) {
          matFriends[i][j] = 0;
        }
      }

      /* Stocke les conversions entre rang et id */
      for (itPers = listPerson.begin(); itPers != listPerson.end(); itPers++) {
        idToRank[(*itPers).second.get_id()] = idToRank.size() -1;
        rankToId[idToRank.size() -1] = (*itPers).second.get_id();
      }

      /* Lecture des donnees et stockage */
      for (i = 0; i < nbLink; i++){
        fscanf(filedata, "%d, %d\n", &x, &y);
        matFriends[idToRank[x]][idToRank[y]] = 1;
      }

    } else {
      /* On va lire la liste et stocker progressivement les données */
      for (i = 0; i < nbLink; i++){
        fscanf(filedata, "%d, %d\n", &x, &y);

        /* On ajoute a x un ami */
        listFriends[x].addFriend(y);

        /* On ajoute a y quelqu'un qui lui fait confiance */
        listFriends[y].addDualFriend(x);
      }

       /* Tri de tous les amis */
      for (itFrie = listFriends.begin() ; itFrie != listFriends.end(); itFrie++) {
        (*itFrie).second.set_id((*itFrie).first);
        (*itFrie).second.sortFriends();
      }

    }

    /* Etape 5 - Lecture du nombre de question */
    fscanf(filedata, "%d\n", &nbQuestion);

    /* Etape 6 - Stockage des questions */
    for (i = 0; i < nbQuestion; i++){
      fscanf(filedata, "%d -> %d\n", &x, &y);
      addQuestion(x, y);
    }

      /* Tri des questions */
      for (itQuest = listQuestion.begin() ; itQuest != listQuestion.end(); itQuest++) {
          sort( (*itQuest).second.begin(), (*itQuest).second.end() );
      }

      analysable = true;
  }

  fclose(filedata);
}

void UserData::clear() {
  /* Remise a zero des attributs */
  nbPerson = 0;
  nbLink = 0;
  nbQuestion = 0;
  analysable = false;
  structFriends = 'x';

  /* Remise a zero des containers */
  listPerson.clear();
  listFriends.clear();
  listQuestion.clear();
  idToRank.clear();
  rankToId.clear();
}


char UserData::defineStructFriends() {
  /* TODO statistiques pour determiner quelle structure choisir
  char choice = 'x';

  cout << "Quelle structure ? Liste (l) ou Matrice (m) ? ";
  while (choice != 'l' && choice != 'm'){
    cin >> choice;
  }

  return choice;*/
  return 'm';
}


bool UserData::is_question(int id1, int id2) {
  map< int, vector<int> >::iterator it;
  vector< int > v;
  bool question;
  unsigned int i;

  question = false;
  i = 0;


  if (listQuestion.find(id1) == listQuestion.end()) {
    question = false;
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

bool UserData::is_analysable() {
  return analysable;
}


void UserData::print() {
  map< int, Person >::iterator it1;
  map< int, vector<int> >::iterator it2;
  unsigned int i;


  cout << "Liste des personnes :" << endl;

  for (it1 = listPerson.begin() ; it1 != listPerson.end(); it1++) {
    (*it1).second.print();
  }

  if (structFriends == 'm') {
    printMatFriends();
  } else {
    printListFriends();
  }

  cout << endl << "Liste des questions : " << endl;
  for (it2 = listQuestion.begin() ; it2 != listQuestion.end(); it2++) {
    for (i = 0; i < (*it2).second.size(); i++) {
      cout << (*it2).first << " -> " << (*it2).second[i] << endl;
    }
  }
}

void UserData::printMatFriends() {
  int i, j;


  for (i = 0; i < nbPerson; i++) {
    cout << rankToId[i] << " : " << endl;

    cout << "   Friends : [ ";
    for (j = 0; j < nbPerson; j++) {
      if (matFriends[i][j]) {
        cout << rankToId[j] << " ";
      }
    }
    cout << "]" << endl;

    cout << "   Dual Friends : [ ";
    for (j = 0; j < nbPerson; j++) {
      if (matFriends[j][i]) {
        cout << rankToId[j] << " ";
      }
    }
    cout << "]" << endl;

    cout << endl;
  }
}

void UserData::printListFriends() {
  map< int, Friends >:: iterator it;


  for (it = listFriends.begin() ; it != listFriends.end(); it++) {
    (*it).second.print();
  }
}

/*=================================*/
