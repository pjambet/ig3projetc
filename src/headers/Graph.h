/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Graph.h
OBJET            : Structure de graphe
--------------------------------------------------------------------------------
DATE DE CREATION : 30/04/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
DETAILS 		 : SCC (Strongly Connected Component) = CFC (Composante Fortement Connexe)

============================================================================= */

#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

/*=================================
Includes
===================================*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <numeric>
#include <cstdio>

#include "Summit.h"
#include "AdjList.h"
#include "AdjMat.h"


/*=================================
Constantes
===================================*/
#define TEST_STRUCT 'l'

using namespace std;


class Graph {
private:

    /* ATTRIBUTS */
    int unsigned m_sizeGraph;
    vector< s_summit > m_tabSummit;
    map< string, int > m_idToRank;
    char m_structGraph;
    bool m_analyzed;

    vector< vector< int > > m_listFriends;
    vector< vector< int > > m_listDualFriends;

    int** m_matFriends;

    int unsigned m_nbSCC;
    vector< vector < int > > m_listSCC;

    int unsigned m_nbDist;
    map< int, vector< int > > m_listQuestion;
    map< int, vector< s_summit > > m_listDist;
    multimap< int, vector< int > > m_listPath;

    /* EXPLICATIONS DES ATTRIBUTS :

    	Structure de stockage et d'analyse du graphe.
    	Les donnees essentielles conservees sont :
    	- m_sizeGraph : Le nombre de sommet dans le graphe
     	- m_tabSummit : Tableau contenant les donnees des sommets
     	- m_idToRank : Permet de faire une association entre une id et son emplacement dans m_tabSummit
      - m_structGraph : Indique si le graphe est analyse avec une structure de matrice (m) ou de liste de voisins (l)
      - m_analyzed : Indique si apres une initialisation, le graphe a deja ete analyse ou pas

      Si la structure est liste, on stocke les donnees dans les attributs suivants :
      - m_listFriend : Un vecteur associant a chaque sommet une liste de fils,
                       m_listFriend[i][j] = x si m_tabSummit[x] est un fils de m_tabSummit[i]
      - m_listDualFriend : Un vecteur associant a chaque sommet une liste de pere,
                           m_listDualFriend[i][j] = x si m_tabSummit[x] est un pere de m_tabSummit[i]

      Si la structure est matrice, on stocke les donnees dans l'attribut suivant :
      - m_matFriends : La matrice d'adjacence associee au donnees

      On stocke aussi les donnees sur les CFC :
      - m_nbSCC : Le nombre de CFC dans le graphe
      - m_listSCC : La liste de liste de CFC
                    Pour i quelconque, m_listSCC[i] contient un vecteur de sommets de la meme CFC

      Ainsi que les donnees sur les distances :
      - m_nbDist : Le nombre de distance a determiner
      - m_listQuestion : On stocke pour chaque point de depart distinct, un vecteur de sommet ou on doit aller
      - m_listDist : On stocke pour chaque point de depart distinct, le tableau de sommet regroupant la distance de ce point vers tous les autres
      - m_listPath : On stocke pour chaque point de depart, un vecteur contenant un chemin a suivre
                     La structure multimap permet d'avoir des chemins differents pour un meme point de depart */

    /* ****************************************************** */
    /* ****************************************************** */

public:

    /* CONSTRUCTEURS ET DESTRUCTEURS */
    Graph ();
    ~Graph ();


    /* ACCESSEURS */
    void setAnalyzed(bool b);
    bool isAnalyzed();

    unsigned int getSizeGraph();
    unsigned int getNbDist();
    unsigned int getNbScc();
    int** getMatFriends();
    vector< s_summit > getTabSummit();
    map< string, int > getIdToRank();
    vector< vector< int > > getListFriends();
    vector< vector< int > > getListDualFriends();
    vector< vector < int > > getListSCC();
    map< int, vector< int > > getListQuestion();
    map< int, vector< s_summit > > getListDist();
    multimap< int, vector< int > > getListPath();

    void setStructGraph(char c);

    bool isAnalysable();
    /* DETAIL : On considere que la condition minimale pour qu'un graphe soit analysable
                est que m_sizeGraph != 0 */


    /* METHODE D'INITIALISATION DE LA CLASSE */

    /* PROCEDURE : initGraph - Initialisation des donnees */
    void initGraph (string& fileNameIn);
    /* COMPLEXITE :
       ENTREE : fileNameIn, nom du fichier d'entree pour initialiser
       ALGORITHME :
         Ouvrir le fichier indique par fileNameIn
         1 - Lecture du nombre de personne
         2 - Lecture des donnees sur les personnes
            Inserer chaque nouvelle personne dans m_tabSummit
            Inserer dans m_idToRank la correspondance entre l'id et sa place dans m_tabSummit
         3 - Lecture du nombre de relation
         INTERMEDIAIRE - Determiner la structure a adopter
         4 - Lecture des relations
            si la structure est une matrice
                "x, y" dans le fichier implique que m_matFriends[m_idToRank[x]][m_idToRank[y]] = 1
            si la structure est une liste
                "x, y" implique qu'on ajoute m_idToRank[y] dans le vecteur correspondant aux amis de x
                et m_idToRank[x] dans le vecteur correspondant aux amis duals de y */


    /* PROCEDURE : clearGraph - Remise a zero des donnees */
    void clearGraph ();
    /* COMPLEXITE : Lineaire
       ENTREE : -
       ALGORITHME :
			Reinitialiser les structures de stockage
			Mettre l'etat du graphe a "non analyse"

			Si la structure est liste
				Reinitialiser la liste des amis et des amis duals
			Sinon
				Desallouer la matrice d'adjacence

			Reinitialiser les CFC
			Reinitialiser les distances */


    /* RECHERCHE */

    /* PROCEDURE : searchSCC - Recherche des CFC */
    void searchSCC ();
    /* COMPLEXITE : Depend de la structure
       ENTREE : -
       ALGORITHME :
            Initialiser m_tabSummit
            Stocker l'intervalle [beg, end] du premier sommet
            Mettre ce premier sommet dans la premiere CFC

            Pour i de 0 au nombre de sommet
                Si l'intervalle est compris dans celui stocke, on ajoute l'element dans la CFC
                Sinon   stocker le nouvel intervalle
                        creer une nouvelle CFC
                        ajouter ce sommet dans la nouvelle CFC */


    /* PROCEDURE : searchDistances - Recherche des distances a determiner */
    void searchDistances ();
    /* COMPLEXITE :
       ENTREE : -
       ALGORITHME :
        */


    /* AUTRES ET OPTIONNELS */

	/* FONCTION : chooseStruct - Determine la structure la mieux adaptee pour analyser le graphe */
    char chooseStruct ();
    /* COMPLEXITE :
       ENTREE : -
       ALGORITHME :
        */


    /* PROCEDURE : saveGraph - Sauvegarde des resultats dans un fichier */
    void saveGraph (string& fileNameOut);
    /* COMPLEXITE : Lineaire
       ENTREE : fileNameOut, nom du fichier d'enregistrement des donnees
                (ce fichier peut ne pas exister, il sera alors cree)
       ALGORITHME :
        */


    /* Affichage */
    /* PROCEDURE : printGraph - Affichage des resultats dans le terminal */
    void printGraph ();
    /* COMPLEXITE : Lineaire
       ENTREE : -
       ALGORITHME :
			Affiche
              - les personnes
              - les composantes fortements connexes
              - les distances demandees
        */
};

#endif // GRAPHE_H_INCLUDED
