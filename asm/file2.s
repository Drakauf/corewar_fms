.name "titi"
.comment "toto"

mov		$1, %r2
mov		%r1, l01(%r2)
mov		%r1, l02(%r2)
fork	l02

l01:

live	$0
xor		%r16, %r16, %r16
jz		l01

l02:

live	$0
xor		%r16, %r16, %r16
jz		l02
