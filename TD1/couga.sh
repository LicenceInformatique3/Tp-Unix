#!/bin/bash

echo "rentrer Nom :"
read nom
echo "rentrer Prenom :"
read prenom
echo "rentrer Numero de rue :"
read numRue
echo "rentrer Nom de la rue :"
read nomRue
echo "rentrer Code Postal"
read codePostal
echo "rentrer Ville"
read ville
adresse="$nom $prenom $numRue $nomRue $codePostal $ville"
echo "$adresse"

echo "Somme gagnée :"
read somme
sommeMsg=""
if [ $somme -gt 0 ]
then
	sommeMsg="vous avez gagné $somme euros"
	echo "$sommeMsg"
elif [ $somme -eg 0 ]
then
	sommeMsg="Désolé vous n'avez pas gagné cette fois !"
	echo "$sommeMsg"
else
	echo "error !"
	exit 1
fi
exit 0

echo "Nom de fichier :"
read file
touch file
if ! [ -r file ]
then
	echo "error file not create !"
	exit 1
fi

$adresse >> file
sommeMsg >> file
