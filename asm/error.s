.name "toto"
.comment "totototo"

live	0
live	%0
live	unknown
live	%:unknown
live	%unknown
live	r1
live	%1, %2

ld		%0, r17
ld		17, r16
ld		r2, r3
ld		%1
ld		unknown, :unknown
ld		%:unknown, %0xff

st		r2, %r1
st		r2, 5+4
st		r2, 2-1
st		r0, r1
st		r1, r01

add		r1, r2, r3d
add		r001, r100, r1lolo
add		r, r, r
add			,	,	
add		%4, 3, 2

sub		"toto", r1, r1
sub		::::::, r1:,r:1
sub		4, %5, %6

and		-:-:-, %, :
and		%, -%, r3
and		-r1, -%4, rx3
and		%004, 43, %0xfff

or		r1, r1, R1
or		.1, #toto
or		5%, -4%, r4

xor		%5%, %3:, r6
xor		1, #%3, r4
xor#	r3, r4, r5

zjmp	%0xe
zjmp	0x0ff
zjmp	%r5
zjmp	r5

ldi		r1, r2, r3, r4
ldi		(r1), r2, r3
ldi		%-15, -15, r5
ldi		12, 12, 12

sti		r3,
sti		r3, , r4
sti		r3, %32, %16# comment

fork	$
fork	%
fork	r
fork	0
fork	,
fork	_
fork	0x
fork	%0xg
fork

lld		%4, %4
lld		label:
lld		l:abel, label2:
lld		:label, r5
00:	01:	02:

lldi
lldi	%1111111111111111111111111111111111111111111111111111111111111111111111, %3, r5
lldi	,,,,,,,,,,,,,,,,,,,
lldi	:,:,:,
