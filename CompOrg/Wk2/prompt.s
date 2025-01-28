# Sample Program for Displaying Prompts

.data
	prompt: .asciz "Enter a number:"
	output: .asciz "The number you entered was:"
.text 0x00400000
.globl main
main:
	addi a7, zero, 4	# display prompt
	la a0, prompt
	ecall
	
	addi a7, zero, 5	# get a number from user
	ecall
	add s0, a0, zero 	#store the number in s0
	
	addi a7, zero, 4	# display output
	la a0, output
	ecall
	
	add a0, s0, zero	# put number in a0
	addi a7, zero, 34	# and display it
	ecall
	
	addi a7, zero, 10	# exit cleanly
	ecall
