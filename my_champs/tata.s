.name		"TaTa << tutu ..."
.comment	"?.?\n?.?"

__start:
	mov		%r1, %r11
	mov		$0x0000000000000001, %r4
	fork	__live
	mov		$0x0f0f0f0f, %r3
	mov		%r3, (__start)
	mov		%r3, (-22)
	mov		%r3, (-23)
	mov		%r3, (-24)
	mov		%r11, (24)
	mov		%r11, (30)
__loop:
	add		%r2, %r4, %r2
	and		%r2, $0x40, %r3
	live	$0x1e101
	jz		__loop
	fork	__live



__live:
	live	$0x1e101
	add		%r2, %r4, %r2
	and		%r2, $0x20, %r3
	jz		__live

__fork:
	mov		%r11, (-20)
	xor		%r2, %r2, %r2
	fork	__live
	jz		__live
