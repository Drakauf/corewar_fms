.name "coucou"
.comment "comment"

ld		%1, r2
sti		r1, %:l01, r2

l01:

live	%0
xor		r16, r16, r16
zjmp	%:l01
