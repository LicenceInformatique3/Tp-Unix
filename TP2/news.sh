#!/bin/bash

if test $# -lt 1
	then
	echo "Usage : news.sh -liste | -lire | -toutlu | -purge"
	echo "-liste : Affiche les noms des fichiers plus récents que .temoin"
	echo "-lire : Affiche les nom et contenu des fichiers plus récents que .temoin"
	echo "-toutlu : Remet .temoin a la date d'aujourd'hui"
	echo "-purge : Supprime toute les nouvelle plus anciennes que .temoin"
	exit 0
fi

FILE="nouvelles"

if test -d "$FILE"
	then
	echo "Dossier déjà existant"
else
	mkdir "$FILE"
fi

touch tmp
echo | ls -t -1 -A ./nouvelles/ >> tmp

for param in "$@"
do
	if test "$param" = "-liste"
		then
		while read -r filename
		do
		if test "$filename" != ".temoin" 
			then
			echo "$filename"
		else
			exit 0
		fi
		done < tmp
	fi
	if test "$param" = "-lire"
		then
		while read -r filename
		do
		if test "$filename" != ".temoin" 
			then
			echo "$filename"
			cat "./$FILE/$filename"
		else
			exit 0
		fi
		done < tmp
	fi
	if test "$param" = "-toutlu"
		then
		touch ".temoin"
	fi
	if test "$param" = "-purge"
		then
		while read -r filename
		do
			if test "$filename" != ".temoin"
				then
				if test "./$FILE/$filename" -ot "./$FILE/.temoin"
					then
					echo "Suppréssion de la nouvelle $filename"
					rm "./$FILE/$filename"
				fi
			fi
		done < tmp
	fi
done
rm tmp
exit 0
