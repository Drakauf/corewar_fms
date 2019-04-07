#!/bin/bash

make -C ../corewar >& /dev/null
make -C ../asm >& /dev/null

if [ ! -x ../corewar/corewar ] || [ ! -x ../asm/asm ] || [ ! -x ../orig/asm ] || [ ! -x ../orig/corewar ]
then
	echo "Missing binaries."
	exit
fi

cp ../corewar/corewar ./
cp ../asm/asm ./
cp ../orig/asm ./o_asm
cp ../orig/corewar ./o_corewar

FILES=$(find -f ../cores/ | grep '\.cor')

for FILE_1 in $FILES
do
	for FILE_2 in $FILES
	do
		echo -n "$FILE_1 - $FILE_2 : "
		./corewar -v 31 -dump 25000 $FILE_1 $FILE_2 > result.log
		./o_corewar -v 31 -d 25000 $FILE_1 $FILE_2 > o_result.log
		diff result.log o_result.log 2>&1 > /dev/null
		if [ $? -eq 1 ]
		then
			echo -e "\033[31;1mFailure\033[0m"
		else
			echo -e "\033[32;1mSuccess\033[0m"
		fi
	done
done

rm -f corewar
rm -f asm
rm -f o_asm
rm -f o_corewar
