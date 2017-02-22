#!/bin/bash
retablir_config(){
	if [ -t .config.old ] ; then
		echo "Rétablit ancien .config"
		mv -f .config.old .config
	fi
}

flag_z=false
if (($#>=1)) ; then
	if [ "$1"="-z" ] ; then
		flag_z=true
		shift
	fi
fi

if [ -f .config ] ; then
	mv -f .config .config.old
fi

touch .config
touch .depend

trap "retablprog1ir_config" 1 2 15
if $flag_z ;then
	cat >.config<< Fin
#fichier .config minimal
#fichier .config généré par $0 le $(date)
SHELL=/bin/bash
Fin
	exit 
fi

echo "saisir un chemin : "
read path

cat >.config<< EoT
#fichier .config généré par $0 le $(date)
HAS_CONFIG=yes
SHELL=/bin/bash
CC=gcc
CFLAGS=-Wall -W -std=c99
CPATHS=
LFLAGS=
LPATHS=
INSTALL_DIR=$path
EoT

if make -v | grep GNU > /dev/null 2>&1 ; then
	echo "HAS_GNUMAKE=yes">>.config
fi
