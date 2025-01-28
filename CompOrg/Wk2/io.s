# CSCI 341
# First RISC-V Program

.data

.text

main: 
	addi a7, zero, 5	# get an integer from user
	ecall
	
	addi a7, zero, 1	# display integer in decimal
	ecall

 	addi a7, zero, 10
 	ecall