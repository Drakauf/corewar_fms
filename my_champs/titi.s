.name		"~ TITI ~ the best"
.comment	"Clone, jump, clone"

start:
	mov		[loop + 21],	r1
	mov		r2,		0			; code copying address
	mov		r3,		148			; code pasting address
	mov		r4,		4			; loop increment
	mov		r5,		44			; loop stop
	mov		r7,		0			; iterator
	mov		r8,		0x08540101	; just to erase my number write,
	mov		[start],		r8	; it is a xor r1, r1, r1 and then
	mov		r8,		0x0109fe01	; zjmp -511
	mov		[start + 4],	r8	; it avoids people to just fork my code

loop:
	mov		r15,		[r2 + r7]		; copy loop content
	mov		[r3 + r7],	r15				; paste loop content
	add		r7,			r7,			r4	; increment of 4 bytes
	xor		r7,			r7,			r5	; if (loop is copied, i.e r7 == 44)
	live	7							; just a live
	jz		123							; then (jump to the next loop)
	xor		r7,			r7,			r5	; else (restore r7 content)
	xor		r9,			r9,			r9	; just to set carry to 1
	jz		loop						; then jump back in the loop
