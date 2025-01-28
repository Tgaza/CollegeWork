.globl sumSquare
.text

# int sumSquare (int x, int y) {
# return mult(x,x)+y;}
sumSquare:
    addi sp, sp, -8     # reserve space on stack
    sw ra, 4 (sp)       # save return address
    sw a1, 0 (sp)       # save y

    add a1, a0, zero    #
    jal ra, mult        # call mult (x,x)

    lw a1, 0 (sp)       # restore y
    add a0, a0, a1      # mult() + y
    lw ra, 4 (sp)       # get return address
    addi sp, sp, 8      # restore stack
    jalr zero, ra, 0

