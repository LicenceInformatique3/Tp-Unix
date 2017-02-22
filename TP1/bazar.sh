#!/bin/bash

echo "Donner un nom de fichier en entrée : "
read inFile
echo "Donner un nom de fichier de sortie : "
read outFile
if test -r $inFile
then
	touch $outFile
else
	echo "Fichier incorrect !"
	exit 1
fi

echo "Entier a : "
read a
echo "Entier b : "
read b
if [ "$a" -lt 0 ] || [ $b -lt $a ]
then
	echo "Erreur a est plus petit que 0 ou b est plsu petit que a !"
	exit 1
fi

head -$b $inFile | tail -$a > $outFile
exit 0
