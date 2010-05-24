/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Summit_unittest.cc
OBJET            : Unit Tests concernant le fichier Summit
--------------------------------------------------------------------------------
DATE DE CREATION : 14/05/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
DETAILS 		 : Ce fichier réalise les tests unitaires afin de verifier et 
				   de conserver le bon fonctionnement des fonctions
				   du fichier Summit.h(cpp)
============================================================================= */

#include <gtest/gtest.h>
#include "../headers/Summit.h"

TEST(Summit, orderBeg) {

	s_summit s1, s2;
	s1.beg = 1;
	s2.beg = 2;
	
	EXPECT_TRUE(orderBeg(s1, s2) );

}

TEST(Summit, orderEnd) {

	s_summit s1, s2;	
	s1.end = 3;
	s2.end = 4;
	
	EXPECT_TRUE(orderEnd(s1, s2) );

}
