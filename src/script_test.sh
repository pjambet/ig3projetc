#!/bin/bash
	
date >> log
for (( i = 10; i < 5000; i+=50 )); do
	echo -n $i " ";
	./GrapheFB -log 1000 10 $i >> log 
done
echo "";


