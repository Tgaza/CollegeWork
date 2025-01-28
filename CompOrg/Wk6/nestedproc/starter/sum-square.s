.globl sumSquare
.text

# int sumSquare (int x, int y) {
# return mult(x,x)+y;}
sumSquare:
   addi sp, sp, -8
   sw ra, 0(sp)
   sw a1, 4(sp)  # store y
   
   addi a1, a0, 0  # a1 = a0 = x
   jal ra, mult
   
   lw a1, 4(sp)
   add a0, a0, a1 # mult(x,x) + y
   
   lw ra, 0(sp)
   addi sp, sp, 8
   
   jalr zero, ra, 0
