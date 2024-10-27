#!/bin/bash
{
for (( i = 1; i < 21; i++ )); do
	mkdir $i
	cd $i
	touch $i.txt
	echo "$i" > $i.txt
	cd -
	ln -s ./$i/$i.txt
	if [[ $(grep "4" ./$i/$i.txt) -eq 0  ]]; then
		rm ./$i/$i.txt
	fi	
done
echo "Hello World" > ./14/14.txt
} &> /dev/null