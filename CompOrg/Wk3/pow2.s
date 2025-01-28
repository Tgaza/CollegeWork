.data 

pow2: .word 1, 2, 4, 8, 16, 32, 64, 128

.text

addi a7, zero, 5 # read int

ecall

addi t0, a0, 0 # save b

ecall # get c into a0

add t0, t0, a0 # a = b + c

la t1, pow2

add t0, t0, t0 # t0 = a * 2

add t0, t0, t0 # t0 = (a*2)+(a*2) = a*4

add t0, t0, t1 # pow2 + a

lw a0, 0(t0) # get the value at pow2[a]

addi a7, zero, 1 # print int

ecall

addi a7, zero, 10 # exit

ecall