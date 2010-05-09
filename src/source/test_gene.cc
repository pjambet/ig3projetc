#include "../headers/Generator.h" 
#include <gtest/gtest.h>

// Teste le constructeur par défault
TEST(GeneTest, resultGeneration) {

	int** matrice;
	int i;
	int born_inf;
	matrice = new int*[1000];
    for (i = 0; i < 1000; i++) {
        matrice[i] = new int[1000];

    }	
	born_inf = 1000 * 0.95;
	EXPECT_LE(born_inf, generateMatrix(1000, matrice, 10));
}

