#!/bin/bash
calculer_somme_md5() #répertoire en paramètre
{
	DIR=$1
	if test $# -lt 1
		then
		exit 1
	fi
	FILES="$(find $DIR -type f -name '*')"
	for f in $FILES
	do
		echo "$(md5sum "$f")"
	done
}

memoriser_somme_md5() #Tableau en paramètre
{
	local -n tab=$1
	tab=()
	while IFS="  " read -r key value
	do
		tab[$value]=$key
	done
}

detecter_doublon() #Trois tableau en paramètres, un d'entrée, deux de sorties
{
	local -n tab_fic=$1
	local -n tab_cpt=$2
	local -n tab_dbl=$3
	tab_cpt=()
	tab_dbl=()
	for i in "${!tab_fic[@]}"
	do
		if [ ${tab_cpt[$i]} ]
			then
			((tab_cpt[$i]=tab_cpt[$i]+1))
			tab_dbl[$i]+=" : $i"
		else
			tab_cpt[$i]=1
			tab_dbl[$i]=${tab_fic[$i]}
		fi
	done
}

afficher_doublons() #Deux tabelaux en entrée
{
	local -n tab_cpt1=$1
	local -n tab_dbl1=$2
	for i in "${!tab_cpt1[@]}"
	do
		if test ${tab_cpt1[$i]} -gt 1
			then
			echo "${tab_dbl1[$i]}"
		fi
	done
}

declare -A array_fic
declare -A array_cpt
declare -A array_dbl
if test $# -ne 1
then
	exit 1
fi
echo "Calcul des sommes md5 ..."
memoriser_somme_md5 array_fic <<< "$(calculer_somme_md5 $1)"
echo "Détection des doublons ..."
detecter_doublon array_fic array_cpt array_dbl
echo "Affichage des doublons ..."
afficher_doublons array_cpt array_dbl
exit 0
