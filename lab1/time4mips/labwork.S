  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #
hexasc:
	andi $v0, $a0, 15 # will get the least significant bit of $s0 and put it in $t0.
	li $t0, 10
	slt $t1, $a0, $t0 # $t1 1 if $a0 < $t0
	bne $t1, $zero ISSMALL # if 1
	nop
	addi $v0, $v0, 0x37
	jr $ra      
	
	ISSMALL: addi $v0, $v0, 0x30
	jr $ra      # return from function
	nop
	
delay: 
	move $t0, $a0
delayinner:
	blt $t0, $zero, delayreturn # if above is false (0 > $a0) then return
	nop
	subi $t0, $t0, 1
	li $a1, 0
	li $a2, 10	#4711
	j delayloop 
	nop	
delayloop:
	beq $a1, $a2, delayinner
	nop
	addi $a1, $a1, 1
	j delayloop
	nop
delayreturn:
	jr $ra
	nop

time2string: 
	PUSH($ra) # Push return address to stack since hexasc will change it ($ra)
	PUSH($s0) # Push s0 to the stack to ensure it's the same after t2s
	PUSH($s1)
	move $s0, $a0
	la $s1, ($a1) # load address stored in a1 into s0
	
	sb $zero, 5($s0)
		
	andi $a0, $s1, 15 # only use the first  four bits
	jal hexasc
	sb $v0, 4($s0) # store return value of hexasc=v0 into address of given a0=s1
	

	andi $a0, $s1, 255 # only use the first  eight bits
	srl $a0, $a0, 4 # shift to the right to only use the four leftmost bits
	jal hexasc
	sb $v0, 3($s0) # store return value of hexasc=v0 into address of given a0=s1
	
	li $t0, 0x3a # colon ascii char
	sb $t0, 2($s0) 
	
	andi $a0, $s1, 4095 # only use the first twelve bits
	srl $a0, $a0, 8 # shift to the right to only use the four leftmost bits
	jal hexasc
	sb $v0, 1($s0) # store return value of hexasc=v0 into address of given a0=s1
	
	andi $a0, $s1, 65535 # use the 16 leftmost bits
	srl $a0, $a0, 12 # shift to the right to only use the four leftmost bits
	jal hexasc
	sb $v0, ($s0) # store return value of hexasc=v0 into address of given a0=s1
	
	POP($s1)
	POP($s0)
	POP($ra)
	jr $ra


	



