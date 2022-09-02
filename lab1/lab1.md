# LAB1

## 1
- Which lines of code had to be changed? Why?
We changed row 14 which loads one to load three. (this is the stepsize)

We changed the row 16 which loads 0x5b (91) to 0x5d (93) since we step by three we need to break at somewhere
divisible by three.

## 2
If the return value is 17 what is the return value?
eight, since we remove all the bits above 15 ???!!!

## 3
- Which registers are saved and restored by your subroutine? Why?
$s0 and $s1 are saved and restored since they are used in the subroutine and saved registers are required to be restored before function exits. $ra is stored since another subroutine is called and will need to use that register.

- Which registers are used but not saved? Why are these not saved?
$a0 and $v0 are used but not stored since they are used as function argument and return value.

- Assume the time is 16:53. Which lines of your code handle the '5'?
```asm
# 109-113
andi $a0, $s1, 255 
srl $a0, $a0, 
jal hexasc
sb $v0, 3($s0) 
```