#! /bin/bash

action=
flag_debug=false
flag_optim=false
flag_warni=false

afficher_usage() 
{
	local nomscript="${0##*/}"
	echo "$nomscript -h|--help"
	echo "$nomscript --touch|--clean fichier.c ..."
	echo "$nomscript [--debug|--optim|--warni] --cc fichier.c ..."
}

if test $# -lt 1
then
	afficher_usage > /dev/stderr
	exit 1
fi

while test $# -gt 0
do
	case "$1" in
		-h|--help) echo "help"; afficher_usage; exit 0;;
		--touch) echo "touch"; action=touch; shift;;
		--clean) echo "clean"; action=clean; shift;;
		--cc) echo "cc"; action=cc; shift;;
		--debug) echo "debug"; flag_debug=true; shift;;
		--optim) echo "optim"; flag_optim=true; shift;;
		--warni) echo "warni"; flag_warni=true; shift;;
		*)break;
	esac
done

modifier_date_fichiers()
{
	for fichier
	do
		if ! test -r "$fichier"
		then
			echo "Erreur, le fichier $fichier n'existe pas." > /dev/stderr
		else
			touch "$fichier"
			echo "Date changée."
		fi
	done
}

obtenir_nom_exec()
{
	echo "${1%%.*}"
}

nettoyer_fichiers() 
{
	for fichier
	do
		if ! test -r "$fichier"
		then
			echo "Erreur, le fichier $fichier n'existe pas." > /dev/stderr
		else
			local exec="$(obtenir_nom_exec "$fichier")"
			if test -r "$exec"
			then
				echo "$exec : suppression"
				rm "$exec"
			else
				echo "$exec : absent"
			fi
		fi
	done		
}

compiler_fichiers()
{
	for fichier
	do
		local exec="$(obtenir_nom_exec "$fichier")"
		if ! test -r "$fichier"
		then
			echo "Le fichier $fichier n'existe pas"
		else
			! test -r "$exec"
			a=$?			
			test "$fichier" -nt "$exec"
			b=$?
			if test "$a" -o "$b"
			then
				local ligne="gcc $fichier "
				if $flag_debug
				then
					ligne+="-g "
				fi
				if $flag_optim
				then
					ligne+="-02 "
				fi
				if $flag_warni
				then
					ligne+="-Wall -W "
				fi
				ligne+="-std=c99 -o $exec"
				eval "$ligne"
			fi
		fi
	done
}

if test "$action" = "touch"
then
	modifier_date_fichiers "$@"
elif test "$action" = "clean"
then
	nettoyer_fichiers "$@"
elif test "$action" = "cc"
then
	compiler_fichiers "$@"
fi
		
