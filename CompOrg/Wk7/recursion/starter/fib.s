# Sample RISC-V program for recursive function call
# fibonacci numbers in RISC-V

   .data
ASK:
   .asciz "\n\nEnter a number n (0<=n<48): "
RESULT:
   .asciz "\nFibonacci(n) is: "

   .text
 #  .globl fib

main:

   # while n in [0..48) output fib(n)

   addi a7, zero, 4    # print string
   la   a0, ASK      # ask for a number
   ecall
   
   addi a7, zero, 5    # read integer
   ecall

   addi t0, zero, 48   
   bgeu a0, t0, done # if !(0 < a0 <= 47) goto done
   
   jal  ra, fib
   
   add  s0, a0, zero  # save result to print
   
   addi a7, zero, 4    # print string
   la   a0, RESULT   # label result
   ecall
   
   addi a7, zero, 1    # print integer
   add  a0, s0, zero  # result from fib earlier
   ecall

   jal zero, main          # and again

done:
   addi a7, zero, 10   # exit
   ecall

# fib(n) = n < 2 ? 1 : fib(n-1) + fib(n-2)    
# a2 - n (volatile, not n upon return)
# a0 - fib(n)
# s0 - fib(n-1) (restored to caller's s0 before return)
# t0 - holds a 1 for a base case beq test
fib:
   # prologue - set up stack, save persistent regs & $ra
    # space for 3 words
    # saving $a0 as caller
    # save return address
    # save $s0, used within
   
   # body of fib
   addi t1, a0, 0   # save incoming a0 to branch on
   
   # base cases: 0 or 1, return 1
      # a0=1, return value
     # if n==0 goto fib_done
    # if n==1 goto fib_done
   
   # recursive cases, return fib(n-1) + fib(n-2)
   # a0 = n-1
    # need a0 after jal
      # fib(n-1)
     # save result
    # restore $a0
    # a0 = n-2
    # fib(n-2)
    # a0=fib(n-2)+fib(n-1)
                    # continues at fib_done...

   #epilogue - restore persistent regs & ra, release stack   
fib_done:
     # restore $s0
     # restore $ra
     # pop the stack frame
    # return to caller
