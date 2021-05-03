        .arch msp430g25453
	.p2align 1,0

	
	.text
jt:
	.word case0
	.word case1
	.word case2
	.word case3
	.word default

	
	.global state_selection
state_selection:
	cmp #4, r12		; r12 - 4, if c = 1 (result is 0 or bigger),
	jc default		; go to default
	
	add r12, r12		; duplicating state
	mov jt(r12), r0		;jumping to address in jt[state]

	
default:
	call #shape_state_default
	pop r0

case0:
	call #shape_state_0
	pop r0

case1:
	call #shape_state_1
	pop r0

case2:
	call #shape_state_2
	pop r0

case3:
	call #shape_state_3
	pop r0


	
	
	
