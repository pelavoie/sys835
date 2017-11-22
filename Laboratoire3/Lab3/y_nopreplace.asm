	.global _y_nopreplace

; x* = a4, vx=a5
; h* = b4, vh=b5
; n = a6
; y = a7
; return = a4
_y_nopreplace:
	zero A7
	mv   A6, B0
loop:
	ldh.d1  *A4++, A5
	|| ldh.d2  *B4++, B5
	sub   B0, 1, B0
	[B0] b loop
	nop   2
	mpy   A5, B5, B5
	nop
	add   B5, A7, A7
	b     B3
	mv    A7, A4
	nop   4

