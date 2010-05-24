/* =============================================================================
PROJET           : projet C ig3 - FACEBOOK
NOM DU FICHIER   : Generator_unittest.cc
OBJET            : Unit Tests concernant le fichier Generator
--------------------------------------------------------------------------------
DATE DE CREATION : 09/05/2010
AUTEUR           : Quentin DREYER / Pierre JAMBET / Michael NGUYEN
--------------------------------------------------------------------------------
DETAILS 		 : Ce fichier réalise les tests unitaires afin de verifier et 
				   de conserver le bon fonctionnement des fonctions
				   du fichier Generator.h(cpp)
============================================================================= */

#include <ctime>
#include <cstring>

#include "../headers/Generator.h" 
#include <gtest/gtest.h>


TEST(Generator, GenerateFile) {

	Generator G;
	int nbpers_th = 0, nbrel_th = 0, nbquest_th = 0;//taille theorique, la taille qu'on lit au debut
	int nbpers_re = 0, nbrel_re = 0, nbquest_re = 0;//taille réelle, egale au nombre de lignes qui suivent
	char chaine[100] = "";// variable "tampon" qui permet de lire le fichier
	char buffer[100];// deuxieme variable "tampon" qui permet de lire le fichier
	bool continuer = true;//booleen utile au parcour du fichier
	char tmp1[100];
	
	//On teste si la structure du fichier est conforme au sujet
	EXPECT_TRUE(G.getDestination().c_str() != NULL);
	
	G.changeOptionAutomatic( "../test/noms.dat", "../test/gene-ut", 1000, 1000, 500);
	G.generateFile();
	
	FILE* fichier = NULL;
	
	ASSERT_TRUE((fichier = fopen(G.getDestination().c_str(), "r")))
		<< "Echec de l'ouverture de " << G.getDestination();
		
	// Lecture des relations
	fscanf(fichier, "%d\n", &nbpers_th);
	while ((fgets(chaine, 100, fichier) ) != NULL && (continuer)) {
		if (((int)chaine[0] >= 65 && (int)chaine[0] <= 90) || ((int)chaine[0] >= 65 && (int)chaine[0] <= 90) ) {
			// si le premier caractere est une lettre
			nbpers_re++;
		}
		else {
			// Le premier caractere n'est pas une lettre
			continuer = false;			
		}
		strcpy(buffer, chaine);
	}
		
	// Lecture des relations
	nbrel_th = atoi(&buffer[0]);
	continuer = true;
 	do {
 		//LIGNE DANGEUREUSE !!!
 		//Déclence une erreur chelou : stack smashing detected
 		//si la taille de tmp1 est "dépassé"
 		fscanf(fichier, "%s", tmp1 );
		nbrel_re++;
		
		if (tmp1[strlen(tmp1) - 1] != ',') {
			continuer = false;
		}
		
	} while ((fgets(chaine, 100, fichier) ) != NULL && (continuer)) ;
 
 	// Lecture des questions
 	nbquest_th = atoi(tmp1);
 	while (fgets(chaine, 100, fichier) != NULL) {
		nbquest_re++;
	}
 	
 	
	fclose(fichier);
	
	EXPECT_EQ(nbpers_re, nbpers_th);
	EXPECT_EQ(nbrel_re, nbrel_th);
	EXPECT_EQ(nbquest_re, nbquest_th);
	
}

// Teste la fonction GenerateMatrix
TEST(Generator, GenerateMatrix) {
	Generator G;
	// Pour chacun des tests, on teste si le nombre réel de sommet et "conforme"
	// au nombre demandé, le test est faux si le nombre est inférieur a 95% du nombre
	// voulu
	
	// On verifie par la meme occasion que le temps de generation ne soit pas trop
	// lent
	
	
	int** matrice;
	int i;
	clock_t t_before, t_after;
	matrice = new int*[1000];
    for (i = 0; i < 1000; i++) {
        matrice[i] = new int[1000];
    }	
    
    // Premier TEST
    t_before = clock();
	
	EXPECT_LE((1000 * 1000 * 0.1) * 0.95, G.generateMatrix(1000, matrice, 1000))	
	<< "La generation n'a pas genere assez de sommets (< 95\% de la valeur saisie.)";
	
	t_after = clock();
	
	EXPECT_GE(0.1, (((double) t_after - t_before) / CLOCKS_PER_SEC))
	<< "La generation est trop longue";
	/*-------------*/
	
	// DEUXIEME TEST
	t_before = clock();
	
	EXPECT_LE((1000 * 1000 * 0.5) * 0.95, G.generateMatrix(1000, matrice, 5000)) 
	<< "La generation n'a pas genere assez de sommets (< 95\% de la valeur saisie.)";
	
	t_after = clock();
	
	EXPECT_GE(0.1, (((double) t_after - t_before) / CLOCKS_PER_SEC))
	<< "La generation est trop longue";
	/*-------------*/
	
	// On delete la matrice de 1000
	for (i = 0; i < 1000; i ++) {
		delete[] matrice[i];
	}
	delete[] matrice;
	
	// On la reinitialise a 2000
	matrice = new int*[2000];
    for (i = 0; i < 2000; i++) {
        matrice[i] = new int[2000];
    }
	
	// TROISIEME TEST
	t_before = clock();
	
	EXPECT_LE((2000 * 2000 * 0.2) * 0.95, G.generateMatrix(2000, matrice, 2000)) 
	<< "La generation n'a pas genere assez de sommets (< 95\% de la valeur saisie.)";
	
	t_after = clock();
	
	EXPECT_GE(0.31, (((double) t_after - t_before) / CLOCKS_PER_SEC))
	<< "La generation est trop longue";
	/*-------------*/
	
	//QUATRIEME TEST
	t_before = clock();
	
	EXPECT_LE((2000 * 2000 * 0.5) * 0.95, G.generateMatrix(2000, matrice, 5000)) 
	<< "La generation n'a pas genere assez de sommets (< 95\% de la valeur saisie.)";

	t_after = clock();
		
	EXPECT_GE(0.35, (((double) t_after - t_before) / CLOCKS_PER_SEC))
	<< "La generation est trop longue";
	/*-------------*/

	
	for (i = 0; i < 2000; i ++) {
		delete[] matrice[i];
	}
	delete[] matrice;
}

TEST(Generator, convertNumToRatio) {
	Generator G;
	
	EXPECT_EQ(10, G.convertNumToRatio(100,10));
	EXPECT_EQ(5, G.convertNumToRatio(2000,2000));
	EXPECT_EQ(4, G.convertNumToRatio(500,100));
}

