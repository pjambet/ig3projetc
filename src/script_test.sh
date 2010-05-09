#!/bin/bash
# Script pour tester le programme avec pleins de fichiers generes.
# Premiere boucle : i => nombre de sommets
# Deuxieme boucle : j => densité de relations
# Troisieme boucle : k => nombre de questions
date >> log
for (( i = 100; i < 2000; i+=100 )); do
	echo -n $i " ";
	for (( j = 1; j < 10; j+=1 )); do
		for (( k=10; k < 1000; k+=20 )); do			
			./GrapheFB -log $i $j $k >> log 			
		done
	done
done
echo "";


