# SAMPLE RISC-V Program for nested function calls

.data
    prompt_one: .asciz "Enter number one:"
    prompt_two: .asciz "Enter number two:"
    NL: .asciz "\n"

.text
main:

    addi a7, zero, 4    # display prompt
    la a0, prompt_one
    ecall

    addi a7, zero, 5    # get a number from user
    ecall
    add s0, a0, zero    #store the number in s0: i

    addi a7, zero, 4    # display prompt
    la a0, prompt_two
    ecall

    addi a7, zero, 5    # get a number from user
    ecall
    
    add s1, a0, zero    #store the number in s1: j

# i, j, k: s0, s1, s2
# k = sumSquare (i,j);

    addi a0,s0,0        # arg0 = i
    addi a1,s1,0        # arg1 = j
    jal ra, sumSquare   # call sumSquare (i,j)
    
    addi s2, a0, 0      # k = sumSquare (i,j)
    
    la a0, NL
    addi a7, zero, 4
    ecall
    
    addi a0, s2, 0
    addi a7, zero, 1
    ecall
	
    addi a7, zero,10
    ecall
