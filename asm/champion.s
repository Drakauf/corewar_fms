.name		"Frantz"
.comment	"petit test..."


	mov		$1, %r2
	mov		%r1, (live_1 + %r2)
	fork	destroy
			
live_1:
	live	$0
	mov		%r1, (live_1 + %r2)
	xor		%r16, %r16, %r16
	jz		live_1

destroy:
	mov		$1001, %r3
	mov		$0x01010101, %r4
	mov		$0x80808080, %r5
	mov		$0xffffffff, %r6

loop:
	sub		%r3, $4, %r3
	mov		%r1, (live_2 + %r2)
live_2:
	live	$0
	
	lmov	0(%r3), %r15
	xor		%r15, %r4, %r14 ; str ^ c32
	sub		%r14, %r4, %r13 ; str - repeat_one
	xor		%r14, %r6, %r12 ; ~str
	and		%r13, %r14, %r14
	and		%r14, %r12, %r14
	and		%r14, %r5, %r14
	jz		loop

;live instruction founded

	and		$0x000000ff, %r15, %r14
	xor		$0x00000001, %r14, %r13 ; byte 1 == 0x01
	jz		
