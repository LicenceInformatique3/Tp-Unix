#!/bin/bash

echo "Donner un nom de fichier : "
read file
if test -r $file
then
	isPair=false
	cat fichier | while  read ligne
	do 
		if [ "$isPair" = true ]
		then
			echo $ligne
			isPair=false
		else
			isPair=true
		fi
	done
else
	echo "Fichier incorrect !"
	exit 1
fi
exit 0
