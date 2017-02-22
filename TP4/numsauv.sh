#! /bin/bash

afficher_usage() {
	echo "USAGE: numsauv.sh [--purge] fichier ..."	
}

verifier_repertoire_svg() 
{	
	if test -e "./svg"
	then
		if ! test -d "./svg"
		then
			rm -f "./svg"
			mkdir "./svg"
			echo "svg crée"
		else
			echo "svg existe déjà"
		fi
	else
		mkdir "./svg"
		echo "svg crée"
	fi		
}

extraire_extension() #fic
{
	echo "${1##*.}"
}

est_entier() #nb
{
	expr 1 + "$1" > /dev/null 2> /dev/null
}

chercher_copie_max() #nomf
{
	local max=0
	local ext=
	local nomf="$1"
	for i in "./svg/$nomf."*
	do
		ext="$(extraire_extension "$i")"
		if ! est_entier "$ext"
		then
			echo "$ext n'est pas un entier" > /dev/stderr
		else
			if test "$ext" -gt "$max"
			then
				max="$ext"
			fi
		fi
	done
	echo "$nomf.$max"		
}

sauvegarder_fichier() #nomf max
{
	local nomf="$1"
	local max="$2"
	
	if cmp "$nomf" "./svg/$nomf.$max" > /dev/null 2> /dev/null
	then
		echo "$nomf identique à svg/$nomf.$max"
	else
		local new_max="$(expr $max + 1)"
		#((max++))
		echo "Copie de $nomf --> svg/$nomf.$new_max"
		cp "svg/$nomf.$max" "svg/$nomf.$new_max"
		
	fi
}

purger_copies() #nomf max
{
	local nomf="$1"
	local max="$2"
	local ext=0
	while test "$ext" -lt "$max"
	do		
		rm -f "./svg/$nomf.$ext" 2> /dev/null
		((ext++))
	done
}

if test "$#" -lt 1
then
	afficher_usage > /dev/stderr
	exit 1
fi

flag_purge=false

case "$1" in
	--purge) flag_purge=true; shift;;
	*) ;;
esac

verifier_repertoire_svg


while test "$#" -gt 0
do
	chercher_copie_max "$1"
	MAX="$(chercher_copie_max "$1")"
	MAX="$(extraire_extension "$MAX")"
	if ! "$flag_purge"
	then
		sauvegarder_fichier "$1" "$MAX"
	else
		purger_copies "$1" "$MAX"
	fi
	shift
done
