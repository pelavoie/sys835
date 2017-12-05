	.global _FilterASM
	
; out* A4
; in*  B4
; coeffs* A6
; gain B6 
; nb   A8

; xv[0-4] A1, A2, A5, A7, A9
; yv[0-4] B1, B2, B5, B7, B9
; coeffs[0-3] A11, B11, A13, B13
; scratch A6 (in loop)
; add/mul tmp B14, B15, A14

_FilterASM:
; preload coefficients
	ldw.d1 *A6++, A11
	ldw.d1 *A6++, B11
	ldw.d1 *A6++, A13
	ldw.d1 *A6++, B13
	mvk 2, A15
	mv A8, B0
	nop 4
loop:
; xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4];
	mv A2, A1
	mv A5, A2
	mv A7, A5
	mv A9, A7
; xv[4] = in[i] * gain;
	ldw *B4++, A9
	nop 4
	mpysp B6, A9, A9
	nop
; yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4];
	mv B2, B1
	mv B5, B2
	mv B7, B5
	mv B9, B7
; (xv[0] + xv[4])
	addsp A1, A9, A14
; ( coeffs[0] * yv[0])
	mpysp A11, B1, B14
; ( coeffs[1] * yv[1])
	mpysp B11, B2, B15
	nop
	addsp B14, B15, B14
; ( coeffs[2] * yv[2])
	mpysp A13, B5, B15
	nop
	addsp B14, B15, B14
; ( coeffs[3] * yv[3])
	mpysp B13, B7, B15
	nop
  	addsp B14, B15, B14
;  2 * xv[2]
	mpysp A15, A5, A6
	nop
	subsp A14, A6, A14
	addsp A14, B14, A14
	stw	A14, *A4++
	sub B0, 1, B0
	[B0] b loop 
	nop 5
	b     B3
	nop   5
	
