.name "titi"
.comment "Je suis un petit oiseau"

	ld %4, r12
	st r1, r12
	st r12, 508
	sti r1, %:start, %6
start:
	xor r15, r15, r15
	live %0x101
	fork %:start
	
live_01:
	live %0x101
	zjmp %:live_01
