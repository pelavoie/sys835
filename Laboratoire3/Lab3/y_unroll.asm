	.global _y_unroll

; x* = a4, vx=a5
; h* = b4, vh=b5
; n = a6
; y = a7
; return = a4
_y_unroll:
	zero A0
	zero B1
	shr  A6, 2, B0
	;mv   A6, B0
loop:
	ldw.d1  *A4++, A5
	|| ldw.d2  *B4++, B5
	sub   B0, 1, B0
	nop 3
	mpy.m1x   A5, B5, A6
	|| mpyh.m2x A5, B5, B6
	nop
	add   A6, A0, A0
	|| add   B6, B1, B1

	ldw.d1  *A4++, A5
	|| ldw.d2  *B4++, B5
	sub   B0, 1, B0
	nop
	[B0] b loop
	nop 2
	mpy.m1x   A5, B5, A6
	|| mpyh.m2x A5, B5, B6
	nop

	add   A6, A0, A0
	|| add   B6, B1, B1

	b     B3
	add   A0, B1, A4
	nop   4

