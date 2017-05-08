#TD 9-1

# II - Script de generation

#!/bin/bash
if((&# < 2)); then
	echo "Usage: $0 prog a1..." > &2
	exit 1
fi
prog = &1
shift
listeo = 
for f; do
	listeo += "${f%.c}.o"
done
touch Makefile || exit 1
{
	echo "$prog: $listeo"
	echo "gcc $listeo -o $prog"
} >> Makefile
for f; do
	pointo = "${f%.c}.o"
	{
		echo "$pointo : $f"
		echo "gcc -Wall -std=c99 -c $f"
	} >> Makefile
done
echo "Terminé"
