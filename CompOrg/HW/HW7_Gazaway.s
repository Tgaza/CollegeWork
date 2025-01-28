
.macro calc_and_store(%reg, %stor) #calls fact with given register and then stores the result into stor
	addi a0, %reg, 0 #store %reg as argument
	jal ra, fact #call factorial procedure
	addi %stor, a0, 0 #store into %stor
.end_macro
.macro newline() #calls fact with given register and then stores the result into stor
	addi a7, zero, 4 #add newline
	la a0, NL
	ecall
.end_macro
.data
	prompt_n: .asciz "How many objects can you choose from: "
	prompt_k: .asciz "How many objects will you be choosing from: "
	
	resultP1: .asciz "The result of C("
	resultP2: .asciz ","
	resultP3: .asciz ") is "
	
	errorNegVal: .asciz "Error: Negative value entered."
	
	NL: .asciz "\n"
.text

main:
	addi a7, zero, 4 #prompt user for n
	la a0, prompt_n
	ecall
	
	addi a7, zero 5 #get user input
	ecall
	addi s0, a0, 0 #store input
	newline()
	addi a7, zero, 4 #prompt user for k
	la a0, prompt_k
	ecall
	
	addi a7, zero 5 #get user input
	ecall
	addi s1, a0, 0 #store input
	newline()
	
	#check for negative input
	#if negative input jump and print error msg, also exit
	blt s0, zero, NegativeVal
	blt s1, zero, NegativeVal
	jal zero, GoodVals #No negative values jump over error msg code
NegativeVal:
	addi a7, zero, 4 #display error msg and then exit
	la a0, errorNegVal
	ecall
	addi a7, zero, 10
	ecall
GoodVals: #start formula
	#   nCk = (n!)/((k!)*(n-1)!) 
	sub s2, s0, s1 #calc n-k and store
	bge s2, zero, NotNegative #if n-k is negative the result will be 0
	addi s6, zero, 0
	jal zero, Skip
NotNegative: #answer is not 0
	calc_and_store(s2, s2) #calculate (n-k)! and store it in s2
	calc_and_store(s0, s3) #calculate n! and store it in s3
	calc_and_store(s1, s4) #calculate k! and store it in s4
	
	mul s5, s4, s2 # t = ((k!)*(n-1)!)
	div s6, s3,s5 # nCk = n!/((k!)*(n-1)!)
	
Skip:
	addi a0, s0, 0 #store n in first arg
	addi a1, s1, 0 #store k in second arg
	addi a2, s6, 0 #store answer in 3rd arg
	jal ra, print_result
	
	addi a7, zero, 10
	ecall
	
	
	
	
	
#function int fact(n)
#if(n<=1) return 1;
#else return n * fact(n-1);
fact: # Procedure Address 8000
	addi sp, sp, -8 # adjust stack for 2 items
	sw ra, 4(sp) # save the return address
	sw a0, 0(sp) # save the argument n
	addi t0, zero, 1 # t0 = 1
	blt t0, a0, L1 # if n > 1, go to L1
	addi a0, zero, 1 #n<=1 -> return 1
	addi sp, sp, 8 # restore stack pointer
	jalr zero, ra, 0 # return to caller
L1: 
	addi a0, a0, -1 #n>1 -> n = n-1
	jal ra, fact # call fact(n -1)
	lw t0, 0(sp) # return from jal and restore n to t0
	lw ra, 4(sp) # restore the return address
	addi sp, sp, 8 # adjust stack pointer and pop 2 items
	mul a0, t0, a0 # return n * fact (n - 1)
	jalr zero, ra, 0 # return to the caller

#function void print_result()
#print("The result of(" + n + "," + k + ") is " + answer);
print_result:
	la t1, resultP1 #load resultP1 text
	la t2, resultP2 #load resultP2 text
	la t3, resultP3 #load resultP3 text
	addi t4, a0, 0 #store first arg which should be n
	addi t5, a1, 0 #store second arg which should be k
	addi t6, a2, 0 #store third arg which should be the answer
	
	addi a7, zero, 4 #display part 1 of the result msg
	addi a0, t1, 0
	ecall
	
	addi a7, zero, 1 #print n
	addi a0, t4, 0
	ecall
	
	addi a7, zero, 4 #display part 2 of the result msg
	addi a0, t2, 0
	ecall
	
	addi a7, zero, 1 #print k
	addi a0, t5, 0
	ecall
	
	addi a7, zero, 4 #display part 3 of the result msg
	addi a0, t3, 0
	ecall
	
	addi a7, zero, 1 #print ans
	addi a0, t6, 0
	ecall
	
	jalr zero, ra, 0
