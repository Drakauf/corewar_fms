.name "titi"
.comment "Je suis un petit oiseau"

	sti r1, %:live_01, %1
	sti r1, %:start, %6
start:
	xor r15, r15, r15
	live %0x101
	fork %:start
	
live_01:
	live %0x101
	zjmp %:live_01
