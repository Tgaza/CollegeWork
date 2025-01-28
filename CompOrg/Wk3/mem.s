.data
A: .space 72
.text
main:
la s3, A

addi s1, zero, 4 # g
addi s2, zero, 12 # h

# A[9] = g + h

add t0, s1, s2 # g+h
sw t0, 36(s3)

li a7, 10    # code to exit
ecall         # ciao!
