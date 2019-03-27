.comment	"Je raconte ma vie"
.name		"Frantz"

	mov		%r1, %r2
	and		%r1, frantz, %r3
	mov		(32), %r1
	mov		%r1, (044)
	add		%r1, %r2, %r1
	sub		%r3, %r3, %r3
	or		(frantz), $32, %r3
	xor		$-10, %r1, %r2
frantz:
	jz		test
	mov		-16(%r1), %r3
	mov		(%r1+%r2), %r3
	mov		%r3, *32(16)
	mov		%r3, (*32+16)

test:
	fork	$6464
	lmov	$32, %r1
	lfork	$6453
	mov		(label), %r7
	add		r1, 56, r3

label:

	live	$5


