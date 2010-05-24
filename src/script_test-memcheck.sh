#!/bin/bash
# Script pour tester le programme avec pleins de fichiers generes.
# Premiere boucle : i => nombre de sommets
# Deuxieme boucle : j => nombre de relations
# Troisieme boucle : k => nombre de questions
date >> ../test/log2
for (( i = 1000; i <= 2000; i+=200 )); do
	ibis=$(($(($i*$i))-$i))
	echo -n $i " ";
	for j in 5 7 10 100 200 500 750 1000; do
		nb_rel=$(($(($j*$ibis))/1000))
		for k in 5 7 10 100 200 500 750 1000; do
			nb_quest=$(($(($k*$ibis))/1000))	
			for (( l = 1; l < 5; l++ )); do		
				valgrind ./Lager --log $i $nb_rel $nb_quest >> ../test/log2 2>&1				
			done
		done
	done
done
echo "";

