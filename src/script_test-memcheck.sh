#!/bin/bash
# Script pour tester le programme avec pleins de fichiers generes.
# Premiere boucle : i => nombre de sommets
# Deuxieme boucle : j => densité de relations
# Troisieme boucle : k => nombre de questions
date >> log
for (( i = 100; i < 2000; i+=100 )); do
	echo -n $i " ";
	for (( j = 100; j < 1000; j+=100 )); do
		for (( k=10; k < 500; k+=50 )); do			
			valgrind ./GrapheFB --log $i $j $k >> log2 2>&1			
		done
	done
done
echo "";


