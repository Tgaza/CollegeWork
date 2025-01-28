	.data
A:  .word	3, 0, 1, 2, 6, -2, 4, 7, 3, 7
g:	.word	17
h:	.word	25
NL: .asciz "\n" # newline string

	.text 		# code starts here 
main: 		    # entry point of the program

	# put g in s1, h in s2 
	
	
	# g = h + A[8]; 
	
    # A[9] = g + h
	 
    # A[12] = h + A[8]
	
	
	li a7, 10	# code to exit 
	ecall 	    # ciao!
