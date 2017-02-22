#!/bin/bash

if  test $# -ge 1 
	then
	for param in "$@"
	do
		echo "$param (O/N) ?"
		read answer
		if test "$answer" = 'O'
			then
			touch tmp
			echo "$param" >> tmp
		fi
	done
else
	(>&2 echo "Erreur, il faut des arguments")
fi
cat tmp
rm tmp
exit0
