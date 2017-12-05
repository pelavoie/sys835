	.global _y_unroll

; x* = a4, vx=a5
; h* = b4, vh=b5
; n = a6
; y = a7
; return = a4
_y_unroll:
	zero A0
	zero B1
	;shr  A6, 1, B0
	mv   A6, B0
loop:
	ldh.d1  *A4++, A5
	|| ldh.d2  *B4++, B5
	[B0] sub   B0, 1, B0
	nop 3
	mpy.m1x   A5, B5, A6
	nop
	add   A6, A0, A0

	ldh.d1  *A4++, A5
	|| ldh.d2  *B4++, B5
	[B0] sub   B0, 1, B0
	nop
	[B0] b loop
	nop 2
	mpy.m1x   A5, B5, A6
	nop

	add   A6, A0, A0

	b     B3
	mv    A0, A4
	nop   4

