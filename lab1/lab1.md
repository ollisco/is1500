# LAB1

## Assignment 1: Analyzing assembly code
**Q1: Which lines of code had to be changed? Why?**

A1: We changed row 14 which loads one to load three. (this is the stepsize)

We changed the row 16 which loads 0x5b (91) to 0x5d (93) since we step by three we need to break at somewhere
divisible by three.

## Assignment 2: Writing your first assembly-language function
> Note to teachers and students: No s-registers may be used, and no registers should be saved.

**Q1: Your subroutine hexasc is called with an integer-value as an argument in register $a0, and returns a return-value in register $v0. If the argument is 17, what is the return-value? Why?**

The return value is eight  
```mips
hexasc:
    # $a0 is 17 here
	andi $v0, $a0, 15 # $v0 = 17 & 15 = 1
	li $t0, 10
	slt $t1, $a0, $t0 # $t1 = 0 (17 !< 10)
	bne $t1, $zero ISSMALL # if 1
	nop
	addi $v0, $v0, 0x37 # $v0 = 1 + 0x37 = 0x38
    # 0x38 is the ascii code for eight
	jr $ra      
	
	ISSMALL: addi $v0, $v0, 0x30
	jr $ra      # return from function
``` 


**Q2: If your solution contains a conditional-branch instruction: which input values cause the instruction to actually branch to another location? This is called a taken branch.**

A2: values less than 10

## Assignment 3: Printing the time
**Q1: Which registers are saved and restored by your subroutine? Why?**

`$s0` and `$s1` are saved and restored since they are used in the subroutine and saved registers are required to be restored before function exits. `$r` is stored since another subroutine is called and will need to use that register.

**Q2: Which registers are used but not saved? Why are these not saved?**

`$a0` and `$v0` are used but not stored since they are used as function argument and return value.

**Q3: Assume the time is 16:53. Which lines of your code handle the '5'?**

```mips
    andi $a0, $s1, 255 
    srl $a0, $a0, 
    jal hexasc
    sb $v0, 3($s0) 
```
## Assignment 4: Programming a simple delay
> Note to teachers and students: check that the assembly code matches the C code.

Code
```mips
delay: 
	move $t0, $a0
delayinner:
	beq $t0, $zero, delayreturn 
	nop
	subi $t0, $t0, 1
	li $a1, 0
	li $a2, 10	
	j delayloop 
	nop	
delayloop:
	bgt $a1, $a2, delayinner
	nop
	addi $a1, $a1, 1
	j delayloop
	nop
delayreturn:
	jr $ra
```

**Q1: If the argument value in register** **`$a0`** **is zero, which instructions in your subroutine are executed? How many times each? Why?**

A1: These are the lines run 
```mips
```mips
delay: 
	move $t0, $a0
delayinner:
	beq $t0, $zero, delayreturn 
	nop
	subi $t0, $t0, 1
	li $a1, 0
	li $a2, 10	
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
```

A1: These are the lines run and the amount of times they are run.
```mips
# once
move $t0, $a0 
# twice
beq $t0, $zero, delayreturn 
nop
subi $t0, $t0, 1
li $a1, 0
li $a2, 10
j delayloop 

# eleven times
beq $a1, $a2, delayinner
# ten times
nop
addi $a1, $a1, 1
j delayloop
nop

# once
jr $ra
```


**Q2: Repeat the previous question for a negative number: -1.**

A2: All of these are run once
```mips
	move $t0, $a0
	beq $t0, $zero, delayreturn
    jr $ra
```
This happens since `$a0` is -1 which we copy into $t0. This causes the `beq`statement to be true and we branch to delayreturn which only returns.