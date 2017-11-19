	.global _w
	.global _child1
; a = a3
; b = b4, bb=b5
; n = a6
; w = a1, ww = a2
; return = a4
_child1:
	mvkl 	_w , A1
	mvkh	_w , A1
	mv		A6 , B0
	mv		A4 , A3
	zero	A4
loop:
		ldh.d1 *A3++,A5
	||	ldh.d2 *B4++,B5
		ldh *A1++,A2
		nop 4

	mpy A2,A5,A5
	nop
	sub A5,B5,A5
	add A5,A4,A4
	sub B0,1,B0
	[B0]	b	loop
	nop 5
