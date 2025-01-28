.globl mult

.text

#function: int mult (int mcand, int mlier)
# product = 0
# while (mlier>0) {
# product += mcand;
# mlier -=1;
# return product
mult:									
    addi t0, zero, 0  # prod = 0

loop:
    bge zero, a1, Fin      # if mlr <=0, goto Fin
    add t0, t0, a0      # prod += mc
    addi a1,a1, -1      # mlr --
    jal zero, loop

Fin:
    addi a0, t0, 0
    jalr zero, ra, 0


