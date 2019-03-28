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

for FILE in $FILES
do
	echo -e "\033[33;1m$FILE\033[0m"
	tail -n 1 $FILE
	./asm $FILE -o test.cor
	if [ -f test.cor ]
	then
		./o_asm $FILE
		diff --text ${FILE/.s/.cor} test.cor | sed 's/^</[31;1m</;s/^>/[32;1m>/;s/$/[0m/'
		rm -f ${FILE/.s/.cor}
	fi
	rm -f test.cor
done

rm -f corewar
rm -f asm
rm -f o_asm
rm -f o_corewar
