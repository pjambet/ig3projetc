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
#include "../headers/Generator.h"

TEST(AdjMat, DefaultConstructor) {
	AdjMat A;

}

TEST(AdjMat, initSCC) {

	// Dans ce test on va verifier le fonctionnement de DFS et DFSD
	
	AdjMat A;
	
	// On va verifier que les d(x) et f(x) sont conformes
	// c-a-d si d(x) < d(y) < f(y) < d(x) si x est avant y dans le 
	// parcours en profondeur de G et que y appartient a l'arbo de x
	
	//A.initData();
	
	A.DFS();
	
    A.sortDescEnd();
    
    A.DFSD();
	
}

TEST(AdjMat, sortAscBeg) {


}

TEST(AdjMat, sortDescEnd) {


}


