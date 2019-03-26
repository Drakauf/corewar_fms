.name "tutu"
.comment "tutu"

mov		r2, 1
mov		[l01 + r2], r1

l01:

live	0
xor		r16, r16, r16
jz		l01
