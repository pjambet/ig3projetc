/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Graph_unittest.cc
OBJET            : Unit Tests concernant le fichier Graph
--------------------------------------------------------------------------------
DATE DE CREATION : 14/05/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
DETAILS 		 : Ce fichier réalise les tests unitaires afin de verifier et 
				   de conserver le bon fonctionnement des fonctions
				   du fichier Graph.h(cpp)
============================================================================= */
#include <string>

#include <gtest/gtest.h>
#include "../headers/Graph.h"
#include "../headers/Generator.h"

TEST(Graph, DefaultConstructor) {
	Graph G;
	EXPECT_EQ(0, (int)G.getNbDist() );
	EXPECT_EQ(0, (int)G.getNbScc() );
	EXPECT_EQ(0, (int)G.getSizeGraph() );
	EXPECT_EQ(NULL, G.getMatFriends() );

}

TEST(Graph, initGraph) {
	string s = "../test/gene-ut";
	Graph Gr;
	Generator Ge;
	
	Ge.changeOptionAutomatic( "../test/noms.dat", "../test/gene-ut", 1000, 10000, 5000);
	Ge.generateFile();
	
	Gr.initGraph(s);

}

TEST(Graph, clearGraph) {
	
	string s = "../test/gene-ut";
	Graph G;
	Generator Ge;
	
	Ge.changeOptionAutomatic( "../test/noms.dat", "../test/gene-ut", 1000, 10000, 5000);
	Ge.generateFile();
		
	G.initGraph(s);
	
	G.clearGraph();
	
	EXPECT_EQ(0, (int)G.getNbDist() );
	EXPECT_EQ(0, (int)G.getNbScc() );
	EXPECT_EQ(0, (int)G.getSizeGraph());
	EXPECT_EQ(NULL, G.getMatFriends());
	EXPECT_EQ(0, (int)G.getIdToRank().size());
	EXPECT_EQ(0, (int)G.getListDist().size());
	EXPECT_EQ(0, (int)G.getListDualFriends().size());
	EXPECT_EQ(0, (int)G.getListFriends().size());
	EXPECT_EQ(0, (int)G.getListPath().size());
	EXPECT_EQ(0, (int)G.getListQuestion().size());
	EXPECT_EQ(0, (int)G.getListSCC().size());
	EXPECT_EQ(0, (int)G.getTabSummit().size());

}

/* 
	J'ai volontairement omis les ut des accesseurs
	qui se seraient résumés a des tests triviaux
*/   
TEST(Graph, searchDistances) {
	
	//TODO

}

TEST(Graph, searchSCCMat) {
	
	//On teste la generation de graphe sur un teste "etalon" dont on connait le 
	//resultat, on compare ce resultat au resultat de la fonction searchSCC
	
	Graph Gr;
	string s = "../test/test-etalon";
	
	Gr.setStructGraph('m');
	Gr.initGraph(s);
	Gr.searchSCC();
	
	//On recupere le resultat de searchSCC
	vector< vector< int > > listSCC = Gr.getListSCC();
	
	//Maintenant on va le comparer au resultat que l'on connait
	
	EXPECT_EQ('m', Gr.getStructGraph());
	//On attend 5 CFC
	
	//1ere CFC
	//La 1ere CFC est composé de 3 sommets
	//Il y a un decalage de 1 entre le resultat et l'id du sommet
	//2 au lieu de 3, 12 au lieu de 13 etc ...
	EXPECT_EQ(3, (int)listSCC[0].size());
	EXPECT_EQ(12, listSCC[0][0]);
	EXPECT_EQ(13, listSCC[0][1]);
	EXPECT_EQ(14, listSCC[0][2]);
	
	//Deuxieme CFC
	EXPECT_EQ(1, (int)listSCC[1].size());
	EXPECT_EQ(11, listSCC[1][0]);
	
	//Troisieme CFC
	EXPECT_EQ(9, (int)listSCC[2].size());
	EXPECT_EQ(0, listSCC[2][0]);
	EXPECT_EQ(2, listSCC[2][1]);
	EXPECT_EQ(1, listSCC[2][2]);
	EXPECT_EQ(3, listSCC[2][3]);
	EXPECT_EQ(4, listSCC[2][4]);
	EXPECT_EQ(6, listSCC[2][5]);
	EXPECT_EQ(5, listSCC[2][6]);
	EXPECT_EQ(7, listSCC[2][7]);
	EXPECT_EQ(8, listSCC[2][8]);
	
	//Quatrieme CFC
	EXPECT_EQ(1, (int)listSCC[3].size());
	EXPECT_EQ(9, listSCC[3][0]);
	
	//Quatrieme CFC
	EXPECT_EQ(1, (int)listSCC[4].size());
	EXPECT_EQ(10, listSCC[4][0]);
		
}


TEST(Graph, searchSCCList) {
	
	Graph Gr;
	string s = "../test/test-etalon";
	
	Gr.setStructGraph('l');
	Gr.initGraph(s);
	Gr.searchSCC();
	
	//On recupere le resultat de searchSCC
	vector< vector< int > > listSCC = Gr.getListSCC();
	
	//Maintenant on va le comparer au resultat que l'on connait
	
	EXPECT_EQ('l', Gr.getStructGraph());
	//On attend 5 CFC	
	//1ere CFC
	//La 1ere CFC est composé de 3 sommets
	//Il y a un decalage de 1 entre le resultat et l'id du sommet
	//2 au lieu de 3, 12 au lieu de 13 etc ...
	EXPECT_EQ(3, (int)listSCC[0].size());
	EXPECT_EQ(12, listSCC[0][0]);
	EXPECT_EQ(13, listSCC[0][1]);
	EXPECT_EQ(14, listSCC[0][2]);
	
	//Deuxieme CFC
	EXPECT_EQ(1, (int)listSCC[1].size());
	EXPECT_EQ(11, listSCC[1][0]);
	
	//Troisieme CFC
	EXPECT_EQ(9, (int)listSCC[2].size());
	EXPECT_EQ(0, listSCC[2][0]);
	EXPECT_EQ(2, listSCC[2][1]);
	EXPECT_EQ(1, listSCC[2][2]);
	EXPECT_EQ(3, listSCC[2][3]);
	EXPECT_EQ(4, listSCC[2][4]);
	EXPECT_EQ(6, listSCC[2][5]);
	EXPECT_EQ(5, listSCC[2][6]);
	EXPECT_EQ(7, listSCC[2][7]);
	EXPECT_EQ(8, listSCC[2][8]);
	
	//Quatrieme CFC
	EXPECT_EQ(1, (int)listSCC[3].size());
	EXPECT_EQ(9, listSCC[3][0]);
	
	//Quatrieme CFC
	EXPECT_EQ(1, (int)listSCC[4].size());
	EXPECT_EQ(10, listSCC[4][0]);
	

}


TEST(Graph, saveGraph) {
	//TODO

}

