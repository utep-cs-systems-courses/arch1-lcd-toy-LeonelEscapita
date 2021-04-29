        .arch msp430g25453
	.p2align 1,0


	.text
states:
	.word default		
	.word 0			
	.word 1			
	.word 2			
	.word 3			

	.text
	.global state_selection
state_selection:
	mov r12, &t1
	cmp #1, t1
	jnz notInState
	cmp #2, t1
	jnz notInState
	cmp #3, t1
	jnz notInState
	cmp #4, t1
	jnz notInState
	add t1, t1
	mov states(t1), r12
	pop r0

notInState:
	add t1, t1
	mov #0, t1
	mov states(t1), r12
	pop r0

	
	
