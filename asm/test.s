.comment	"Je raconte ma vie"
.name		"Frantz"

	mov		%r1, %r2
	and		%r1, $0x0fff, %r3

label:

	live	$5

=======

(*) -> (.comment) ------------------> (.name) -------------> (mov) ------------> (and) --------------> (label:) ------------> (live) ----> NULL
		   ||                            ||                    ||                 ||                                            ||
	   ("Je raconte ma vie")		("Frantz")               (%r1)               (%r1)                                         ($5)
	                                                           ||                 ||
															 (%r2)             ($0x0fff)
															                      ||
                                                                                 (%r3)
