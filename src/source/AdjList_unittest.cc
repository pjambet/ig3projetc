/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : AdjList_unittest.cc
OBJET            : Unit Tests concernant le fichier AdjList
--------------------------------------------------------------------------------
DATE DE CREATION : 14/05/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
DETAILS 		 : Ce fichier réalise les tests unitaires afin de verifier et 
				   de conserver le bon fonctionnement des fonctions
				   du fichier AdjList.h(cpp)
============================================================================= */

#include <string>
#include <gtest/gtest.h>
#include "../headers/AdjList.h"
#include "../headers/Graph.h"
#include "../headers/Generator.h"

TEST(AdjList, DefaultConstructor) {
	
	AdjList Al;
	
	EXPECT_EQ(0, Al.getSize()) ;
	EXPECT_EQ(0, (int)Al.getGraph().size() );
	EXPECT_EQ(0, (int)Al.getGraphDual().size() );
	EXPECT_EQ(0, (int)Al.getTabSummit().size() );

}

//Test inutile, réalisé dans graph_unittest
//TEST(AdjList, initSCC) {

//	Graph Gr;
//	string s = "../test/gene-ut";
//	AdjList Al;
//	
//	vector< s_summit > tabSummit;
//	vector< vector< int > > listFriends;
//    vector< vector< int > > listDualFriends;
//    	
//	Gr.initGraph(s);
//	
//	tabSummit = Gr.getTabSummit();
//	listFriends = Gr.getListFriends();
//	listDualFriends = Gr.getListDualFriends();
//	
//	Al.initData(tabSummit, listFriends, listDualFriends);
//	
//	Al.initSCC();	
//	
//}

TEST(AdjList, sortDescEnd) {
	
	AdjList Al;
	Graph Gr;
	Gr.setStructGraph('l');
	string s = "../test/gene-ut";
	Generator Ge;
	
	Ge.changeOptionAutomatic( "../test/noms.dat", "../test/gene-ut", 100, 100, 50);
	Ge.generateFile();
	
	vector< s_summit > tabSummit;
	vector< vector< int > > listFriends;
    vector< vector< int > > listDualFriends;
	
	Gr.initGraph(s);
	
	tabSummit = Gr.getTabSummit();	
	listFriends = Gr.getListFriends();	
	listDualFriends = Gr.getListDualFriends();
	
	
	
	Al.initData(tabSummit, listFriends, listDualFriends);
	Al.DFS();
	Al.sortDescEnd();
	for(int i = 0; i < (int)Gr.getSizeGraph() - 1; i++ ) {
		EXPECT_GT(Al.getTabSummit(i).end, Al.getTabSummit(i + 1).end);
	}
		
	
}

TEST(AdjList, sortAscBeg) {
	
	AdjList Al;
	Graph Gr;
	Gr.setStructGraph('l');
	Generator Ge;
	
	Ge.changeOptionAutomatic( "../test/noms.dat", "../test/gene-ut", 100, 100, 50);
	Ge.generateFile();
	
	string s = "../test/gene-ut";
	
	vector< s_summit > tabSummit;
	vector< vector< int > > listFriends;
    vector< vector< int > > listDualFriends;
    	
	Gr.initGraph(s);
	
	tabSummit = Gr.getTabSummit();
	listFriends = Gr.getListFriends();
	listDualFriends = Gr.getListDualFriends();
	
	Al.initData(tabSummit, listFriends, listDualFriends);
	
	Al.DFS();
	Al.sortDescEnd();
	Al.DFSD();
	Al.sortAscBeg();
	
	for(int i = 0; i < (int)Gr.getSizeGraph() - 1; i++ ) {
		EXPECT_LT(Al.getTabSummit(i).beg, Al.getTabSummit(i + 1).beg);
	}
}


