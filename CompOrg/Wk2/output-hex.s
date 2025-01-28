# CSCI 341
# Display Integer in Hex format

.data

.text

main: 

	lui t0, 0x000DEAE0
	addi t0, t0, 0xFFFFFEED
	addi a7, zero, 1		# get an integer from user
	addi a0, t0, 0
	ecall
	
	addi a7, zero, 10	# exit cleanly
	ecall
