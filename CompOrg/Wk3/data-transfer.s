	.data
A:  .word	3, 0, 1, 2, 6, -2, 4, 7, 3, 7
g:	.word	17
h:	.word	25

	.text 		# code starts here 
main: 		    # entry point of the program

	# put g in s1, h in s2 
	la t0, g
	lw s1, 0(t0)
	
	la t0, h
	lw s2, 0(t0)
	
	# g = h + A[8]; 
	la t0, A
	lw t1, 32(t0) # t1 = A[8]
	add s1, s2, t1

    # A[9] = g + h
	add t2, s1, s2
	sw  t2, 36(t0)  
	 
    # A[12] = h + A[8]
	
	sw s1, 48(t0)
	
	addi a7, zero, 10	# code to exit 
	ecall 	    # ciao!
