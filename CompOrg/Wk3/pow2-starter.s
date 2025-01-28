.data 

pow2: .word 1, 2, 4, 8, 16, 32, 64, 128

.text

addi a7, zero, 5 # read int

ecall


 # save b

 # get c into a0

 # a = b + c

# get pow2[a]


addi a7, zero, 1 # print int pow2[a]

ecall

addi a7, zero, 10 # exit

ecall
