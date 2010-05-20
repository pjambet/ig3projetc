#!/bin/bash
# Script pour tester le programme avec pleins de fichiers generes.
# Premiere boucle : i => nombre de sommets
# Deuxieme boucle : j => nombre de relations
# Troisieme boucle : k => nombre de questions
date >> log
for (( l = 1; l <= 5; l++ )); do
	for (( i = 200; i < 2000; i+=400 )); do
		echo -n $i " ";
		for (( j = 1; j < 100; j+=20 )); do
			nb_rel=$(($(($j*$i))/100))
			for (( k=1; k < 100; k+=20 )); do
				nb_quest=$(($(($k*$i))/100))			
					./GrapheFB --log $i $nb_quest $nb_rel >> log4 			
			done
		done
	done	
done
echo "";


