  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0, 15	# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11	# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #

hexasc:
	andi $v0, $a0, 15 # will get the least significant bit of $s0 and put it in $t0.
	li $t0, 9
	slt $t1, $a0, $t0 # $t1 1 if $a0 < $t0
	bne $t1, $zero ISSMALL # if 1
	beq $t1, $zero ISLARGE
	
	ISSMALL: addi $v0, $v0, 0x30
	jr $ra      # return from function
	
	ISLARGE: addi $v0, $v0, 0x37
	jr $ra      # return from function


