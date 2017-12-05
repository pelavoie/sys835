	.global _y_pipelined

; x* = a4, vx=a2
; h* = b4, vh=b2
; n = a6
; y:return = a4
_y_pipelined: .asmfunc
	mv 	 A4,A1
	mv 	 B4,B1
	mv   A6, B0
	zero A4
c0:
		ldh.d1  *A1++, A2
|| 		ldh.d2  *B1++, B2

c1:
		ldh.d1  *A1++, A2
|| 		ldh.d2  *B1++, B2
||[B0]	sub.l2	B0,1,B0

c2:
		ldh.d1  *A1++, A2
|| 		ldh.d2  *B1++, B2
||[B0]	sub.l2	B0,1,B0
||[B0]	b.s2	loop

c3:
		ldh.d1  *A1++, A2
|| 		ldh.d2  *B1++, B2
||[B0]	sub.l2	B0,1,B0
||[B0]	b.s2	loop

c4:
		ldh.d1  *A1++, A2
|| 		ldh.d2  *B1++, B2
||[B0]	sub.l2	B0,1,B0
||[B0]	b.s2	loop

c5:
		ldh.d1  *A1++, A2
|| 		ldh.d2  *B1++, B2
||[B0]	sub.l2	B0,1,B0
||[B0]	b.s2	loop
||		mpy.m1x	A2,B2,A3

c6:
		ldh.d1  *A1++, A2
|| 		ldh.d2  *B1++, B2
||[B0]	sub.l2	B0,1,B0
||[B0]	b.s2	loop
||		mpy.m1x	A2,B2,A3

loop:   ldh .D1  *A1++,A2
||      ldh .D2  *B1++,B2
|| [B0] sub .L2  B0,1,B0
|| [B0] B   .S2  loop
||      mpy .M1x A2,B2,A3
||      add .L1  A4,A3,A4
	nop 5
	b	B3
	nop 5
	.endasmfunc


