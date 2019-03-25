#!/bin/bash

make -C ../corewar
make -C ../asm

FILES=$(find asm_files -type f)

if [ ! -x ../asm/asm ]
then
	echo "Missing binary asm"
else
	mv ../asm/asm ./
fi

for FILE in $FILES
do
	CHECKER=$(echo $FILE | sed 's/asm_files/asm_tests/g' | sed 's/\.s/\.sh/g')
	/bin/bash $CHECKER
done

rm -f asm

FILES=$(find cw_files -type f)

if [ ! -x ../corewar/corewar ]
then
	echo "Missing binary corewar"
	FILES=""
else
	mv ../corewar/corewar ./
fi


for FILE in $FILES
do
	CHECKER=$(echo $FILE | sed 's/cw_files/cw_tests/g' | sed 's/\.cor/\.sh/g')
	/bin/bash $CHECKER
done

rm -f corewar
