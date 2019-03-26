.name "Frantz"
.comment "Comment"

	mov		$0x32, %r1
	mov		(32), %r1
	
	mov		%r1, %r2
	mov		%r1, (32)

	mov		32(16), %r3
	mov		*32(16), %r3
	mov		*16(%r1), %r3
	mov		-16(%r2), %r3

	mov		%r3, 32(16)
	mov		%r3, *32(16)
	mov		%r3, *16(%r1)
	mov		%r3, -16(%r2)

	mov		(0x32 + 16), %r3
	mov		(*32+-16), %r3
	mov		(*-16+ %r1), %r3
	mov		(-16 +%r2), %r3
	mov		(%r2+%r3), %r4

	mov		%r3, (044+16)
	mov		%r3, (*0045+ 16)
	mov		%r3, (*0x16 +%r1)
	mov		%r3, (0x + %r2)
	mov		%r3, (%r2 + %r2)


	lmov		32(16), %r3
	lmov		*32(16), %r3
	lmov		*16(%r1), %r3
	lmov		-16(%r2), %r3

	lmov		$32, %r2
