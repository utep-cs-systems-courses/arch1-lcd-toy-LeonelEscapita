	.arch msp430g2553
	.p2align 1,0


	.text
	.global toggle_green
	
toggle_green:
	cmp #0, &red_on
	jz out
	xor #1, &green_on
	mov #1, r12
out:                     	;r12 is for changed to become the returned value
	pop r0			;return from this function call
