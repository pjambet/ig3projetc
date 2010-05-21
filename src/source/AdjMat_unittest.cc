/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : AdjMat_unittest.cc
OBJET            : Unit Tests concernant le fichier AdjMat
--------------------------------------------------------------------------------
DATE DE CREATION : 14/05/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
DETAILS 		 : Ce fichier réalise les tests unitaires afin de verifier et 
				   de conserver le bon fonctionnement des fonctions
				   du fichier AdjMat.h(cpp)
============================================================================= */

#include <gtest/gtest.h>
#include "../headers/AdjMat.h"
#include "../headers/Graph.h"
#include "../headers/Generator.h"

TEST(AdjMat, DefaultConstructor) {
	AdjMat A;

}

TEST(AdjMat, initSCC) {

	// Dans ce test on va verifier le fonctionnement de DFS et DFSD
	
	AdjMat A;
	Graph Gr;
	
	vector< s_summit > tabSummit;
		
	Gr.initGraph(s);
	
	tabSummit = Gr.getTabSummit();
	
	A.initData(tabSummit, Gr.getMatFriends());
	
	A.initSCC();	
	
	
}

TEST(AdjMat, sortDescEnd) {
	
	AdjMat A;
	Graph Gr;
	Generator Ge;
	
	Ge.changeOptionAutomatic( "../test/noms.dat", "../test/gene_ut", 100, 100, 50);
	Ge.generateFile();
	
	string s = "../test/gene_ut";
	
	vector< s_summit > tabSummit;
		
	Gr.initGraph(s);
	
	tabSummit = Gr.getTabSummit();
	
	A.initData(tabSummit, Gr.getMatFriends());
	
	A.DFS();
	A.sortDescEnd();
	
	for(int i = 0; i < (int)Gr.getSizeGraph() - 1; i++ ) {

		EXPECT_GT(A.getTabSummit(i).end, A.getTabSummit(i + 1).end);
	}
		
	
}

TEST(AdjMat, sortAscBeg) {
	
	AdjMat A;
	Graph Gr;
	Generator Ge;
	
	Ge.changeOptionAutomatic( "../test/noms.dat", "../test/gene_ut", 100, 100, 50);
	Ge.generateFile();
	
	string s = "../test/gene_ut";
	
	vector< s_summit > tabSummit;
		
	Gr.initGraph(s);
	
	tabSummit = Gr.getTabSummit();
	
	A.initData(tabSummit, Gr.getMatFriends());
	
	A.DFS();
	A.sortDescEnd();
	A.DFSD();
	A.sortAscBeg();
	
	for(int i = 0; i < (int)Gr.getSizeGraph() - 1; i++ ) {

		EXPECT_LT(A.getTabSummit(i).beg, A.getTabSummit(i + 1).beg);
	}

}


