# sample RISC-V pogram for branch instructions and do..while loop

# i = 0; j= 2; h=8
# do { g=g+A[i]; i=i+j;}
#while (i!=h}

#g: s1; h:s2; i: s3; j: s4; &A[0]: s5

.data
    A:	.word	0,1,2,3,4,5,6,7,8,9,10
    newline:	.asciz		"\n"

.text
    .globl main

    main:
        la   s5, A

        addi s1, zero, 0	# s1 = 0
        addi s2, zero, 8    # s2 = 8
        addi s3, zero, 0    # s3 = 0
        addi s4, zero, 2    # s4 = 2
        

# loop: g = g+ A[i];
# i = i+j;
# if (i!h) goto Loop;

    loop:
        slli t0, s3, 2
        add t0, s5, t0
        lw t0, 0 (t0)
        add s1, s1, t0
        add s3, s3, s4
        bne s3, s2, loop
	   
	  # Return.
	  addi   a7, zero, 10		# Load system call number
	  ecall		
