	.global _y_parallel

; x* = a4, vx=a5
; h* = b4, vh=b5
; n = a6
; y = a7
; return = a4
_y_parallel:
	zero A7
	mv   A6, B0
loop:
	ldh.d1  *A4++, A5
	|| ldh.d2  *B4++, B5
	nop   4
	mpy   A5, B5, B5
	nop
	add   B5, A7, A7
	sub   B0, 1, B0
	[B0] b loop
	nop   5
	mv    A7, A4
	b     B3
	nop   5

