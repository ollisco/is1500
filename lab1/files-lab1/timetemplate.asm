  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
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
	
	
delay: # $a0=ms : int
	PUSH($s0)
	move $s0, $a0
	blt $zero, $s0, delayreturn # if above is false (0 > $a0) then return
	nop
	subi $s0, $s0, 1
	li $a0, 0
	li $a1, 4711	
	j delayloop 
	nop
	

delayloop:
	bgt $a0, $a1, delay
	nop
	addi $a0, $a0, 1
	j delayloop
	nop

delayreturn:
	POP($s0)
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


	
