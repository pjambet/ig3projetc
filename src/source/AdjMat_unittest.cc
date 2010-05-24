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

#include <string>
#include <gtest/gtest.h>
#include "../headers/AdjMat.h"
#include "../headers/Graph.h"
#include "../headers/Generator.h"

TEST(AdjMat, DefaultConstructor) {
	
	AdjMat Am;
	
	EXPECT_EQ(0, Am.getSize());
	EXPECT_EQ(NULL, Am.getGraph() );
	EXPECT_EQ(0, (int)Am.getTabSummit().size() );

}


// Test inutile, réalisé dans graph_unittest
//TEST(AdjMat, initSCC) {

//	Graph Gr;
//	string s = "../test/gene-ut";
//	AdjMat Am;
//	
//	vector< s_summit > tabSummit;
//		
//	Gr.initGraph(s);
//	
//	tabSummit = Gr.getTabSummit();
//	
//	Am.initData(tabSummit, Gr.getMatFriends());
//	
//	Am.initSCC();	
//	
//}

TEST(AdjMat, sortDescEnd) {
	
	AdjMat Am;
	Graph Gr;
	string s = "../test/gene-ut";
	Generator Ge;
	
	Ge.changeOptionAutomatic( "../test/noms.dat", "../test/gene-ut", 100, 100, 50);
	Ge.generateFile();
	
	vector< s_summit > tabSummit;
		
	Gr.initGraph(s);
	
	tabSummit = Gr.getTabSummit();
	
	Am.initData(tabSummit, Gr.getMatFriends());
	
	Am.DFS();
	Am.sortDescEnd();
	
	for(int i = 0; i < (int)Gr.getSizeGraph() - 1; i++ ) {
		EXPECT_GT(Am.getTabSummit(i).end, Am.getTabSummit(i + 1).end);
	}
		
	
}

TEST(AdjMat, sortAscBeg) {
	
	AdjMat Am;
	Graph Gr;
	Generator Ge;
	
	Ge.changeOptionAutomatic( "../test/noms.dat", "../test/gene-ut", 100, 100, 50);
	Ge.generateFile();
	
	string s = "../test/gene-ut";
	
	vector< s_summit > tabSummit;
		
	Gr.initGraph(s);
	
	tabSummit = Gr.getTabSummit();
	
	Am.initData(tabSummit, Gr.getMatFriends());
	
	Am.DFS();
	Am.sortDescEnd();
	Am.DFSD();
	Am.sortAscBeg();
	
	for(int i = 0; i < (int)Gr.getSizeGraph() - 1; i++ ) {
		EXPECT_LT(Am.getTabSummit(i).beg, Am.getTabSummit(i + 1).beg);
	}
}

TEST(AdjMat, isImportant) {

	//TODO
	
}



