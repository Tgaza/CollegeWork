    .data
prompt: .asciz "Enter an integer: "
data: .byte 4,3,5,1

    .text
main:
    la s0, data
    
    #print data[0] (a byte)
    lb  a0, 0(s0)   # copy data[0] into a0
    addi a7, zero, 1   # code to write int in decimal
    ecall

    #print data[2] (a byte)
    lb  a0, 2(s0) # copy data[2] into a0
    addi a7, zero, 1   # code to write int in decimal
    ecall
    
    #print prompt[7] (a byte)
    la s1, prompt
    lb  a0, 7(s1) # copy prompt[7] into a0
    addi a7, zero, 1   # code to write int in decimal
    ecall

    li a7, 10    # code to exit
    ecall         # ciao!
