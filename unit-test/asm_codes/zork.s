.name "zork"
.comment "just doing lives"

entry:
	fork	%0
	sti		r1,%:live,%1
	ld		%10,r15
	and		r1,%0,r1
live:
	live	%1
	zjmp	%:live

#this should work...
