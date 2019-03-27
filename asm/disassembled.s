.name "titi"
.comment "toto"

ld %1, r2
sti r1, %15, r2
sti r1, %22, r2
fork %16
live %0
xor r16, r16, r16
zjmp %-10
live %0
xor r16, r16, r16
zjmp %-10
