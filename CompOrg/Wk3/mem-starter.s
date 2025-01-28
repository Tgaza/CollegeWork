.data
A: .space 72
.text
main:
la s3, A

addi s1, zero, 4 # g
addi s2, zero, 12 # h

# A[9] = g + h



li a7, 10    # code to exit
ecall         # ciao!
