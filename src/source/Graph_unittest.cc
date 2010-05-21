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

TEST(Graph, DefaultConstructor) {
	Graph G;
	EXPECT_EQ(0, (int)G.getNbDist() );
	EXPECT_EQ(0, (int)G.getNbScc() );
	EXPECT_EQ(0, (int)G.getSizeGraph() );
	EXPECT_EQ(NULL, G.getMatFriends() );

}

TEST(Graph, initGraph) {
	string s = "../test/gene_ut";
	Graph G;
	
	G.initGraph(s);

}

TEST(Graph, clearGraph) {
	
	string s = "../test/gene_ut";
	Graph G;
	
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

/* J'ai volontairement omis les ut des accesseurs
   qui se seraient résumés a des tests triviaux
TEST(Graph, isAnalysable) {


}

TEST(Graph, isAnalyzed) {


}

TEST(Graph, setAnalyzed) {


}

TEST(Graph, getSizeGraph) {


}
*/
TEST(Graph, searchDistances) {


}

TEST(Graph, searchSCCMat) {
	
	Graphe Gr;
	
	Gr.setStructGraph('m');
	Gr.searchSCC();
		
}


TEST(Graph, searchSCCList) {
	
	Graphe Gr;
	
	Gr.setStructGraph('l');
	Gr.searchSCC();

}


TEST(Graph, saveGraph) {


}

