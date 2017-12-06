	.global _y_unroll

; x* = a4, vx=a5
; h* = b4, vh=b5
; n = a6
; y:return = a4
;[B0] sub   B0, 1, B0

_y_unroll: .asmfunc
	zero A0
	zero B1
	shr  A6, 3, B0 ; right shift by 8 (loop unrolled 4x2)
loop:

	ldw.d1  *A4++, A5
 || ldw.d2  *B4++, B5
 	nop 4
	mpy.m1x   A5, B5, A6
 ||	mpyh.m2x   A5, B5, B6
	nop
	add.l1   A6, A0, A0
 || add.l2 	  B6, B1, B1

	ldw.d1  *A4++, A5
 || ldw.d2  *B4++, B5
 	nop 4
	mpy.m1x   A5, B5, A6
 ||	mpyh.m2x   A5, B5, B6
	nop
	add.l1   A6, A0, A0
 || add.l2 	  B6, B1, B1

	ldw.d1  *A4++, A5
 || ldw.d2  *B4++, B5
 	nop 4
	mpy.m1x   A5, B5, A6
 ||	mpyh.m2x   A5, B5, B6
	nop
	add.l1   A6, A0, A0
 || add.l2 	  B6, B1, B1

	ldw.d1  *A4++, A5
 || ldw.d2  *B4++, B5
 	nop 4
	mpy.m1x   A5, B5, A6
 ||	mpyh.m2x   A5, B5, B6
 [B0] sub B0, 1, B0
	add.l1   A6, A0, A0
 || add.l2 	  B6, B1, B1

 [B0] b loop
	nop 5
	b     B3
	add   A0, B1, A4
	nop   4
 	.endasmfunc
