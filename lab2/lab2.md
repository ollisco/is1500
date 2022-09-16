## Assignment 1: Basic Control-Flow 
```c

int is_prime(int n)
{
  // check if n is prime
  int i;
  for (i = 2; i <= sqrt(n); i++)
  {
    if (n % i == 0)
      return 0;
  }
  return 1;
}
```

## Assignment 2: Functions and Side Effects
**Q1: What does it mean when a function does not return a value? How do you state that in a
program? How can then the function (or more precisely, the procedure) perform anything
useful?**

A1: A function that does not return a value is called a `void` function and has the keyword `void` in front of the function name. We do not have a reciever of this funtions meaning the funtion stands on its own and we do not have to do anything else than call it. This can be used to:
- Operate on data that we send in as a pointer. e.g. 
```c
void foo(int* n)
{
    (*n)++;
}   
``` 
or 
- Output data to the terminal for example.
```c
void bad(int m) 
{
    printf("%d", m);
}
``` 
**Q2: How did you implement the side effect that is needed to make print_number behave correctly?**

A2: A global variable was used, one could also use another parameter in the print_number that the print_primes function increases and resets.

## Assignment 3: Arrays 
**Q3: How did you represent the marking of 'prime' and 'not a prime' in the memory array?**

A3: as 0

**Q1: Which are the main steps in the algorithm? How have you implemented these steps?**

A1: The steps are:
  1. Generate array (in heap uses malloc)
  2. Fill array with numbers 2-n
  3. Run sieves algorithm fillin non primes with zeroes
  4. print values im array != 0 (primes)
  5. (heap uses free to realease memory)

**Q2: What is the largest prime number that you can print within 2 seconds of computation? What is the largest number you can print within 10 seconds? Is it the same for print_prime.c, sieves.c, and sieves-heap.c? Why or why not?**

A2: sieves.c is both able to print all numbers before seg fault in the two second window. print primes does not have to allocate all memory at once on the stack and can go further even though it is slower. print sieves heap store the memory on stack and can therefore co past seg fault. 


## Assignment 4: Pointers
**Q1: Explain how you get the pointer addresses to the two char arrays (text1 and text2) and the counter variable (count) in function work()**

A1: They are global variables

**Q2: What does it mean to increment a pointer? What is the difference between incrementing the pointer that points to the ASCII text string, and incrementing the pointer that points to the integer array? In what way is the assembler code and the C code different?**

A2: To increment a pointer means to increase the value which is a memory address meaning it will point to the next position of the allocated memory type.

**Q3: What is the difference between incrementing a pointer and incrementing a variable that a pointer points to? Explain how  your code is incrementing the count variable.**

A3: The difference is either changing the memory address or changing a value at a given adddress. Currently the count variable is just a global variable since it needs to pass the endian test.


**Q4: Explain a statement in your code where you are dereferencing a pointer. What does this mean? Explain by comparing with the corresponding assembler code.**

A4: Code
```c
  for (int i = 0; i < strlen(text); i++)
  {
    int hex = (int)(*(text + i));
    *(list + i) = hex;
    count++;
  }
```
in this for-loop inside copycodes we have to dereferencings of pointers.

```c
int hex = (int)(*(text + i));
```
Since text is a pointer to the fist position of the 'char array', incrementing the address with i will get each address in the string from start to finish. We then deference that address to get the actual value that the memory address is pointing and cast it to an int.

```c
*(list + i) = hex;
```
Here we again grab the equivalent address in the list array (int*) and deference it to set the value to `hex`. If we do not dereference here we set the pointer to point to hex which will prob lead to segmentation fault.


**Q5:Is your computer using big-endian or little-endian? How did you come to your conclusion? Is there any benefit of using either of the two alternatives?**

A5: M1 MacBook has two CPU architecures. Intel x86 and ARM. Both of these use little endian though. 
 
This can be clearly done in C 
```c
#include <inttypes.h>
#include <stdio.h>
int main(void)
{
    uint16_t data = 1; // two bytes
    uint8_t *ptr; // one byte

    ptr = (uint8_t *) &data; // cast the address of data to a pointer to a byte
    if (*ptr == 0)
    {
        printf("Big\n");
    }
    else if (*ptr == 1)
    {
        printf("Little\n");
    }
    return 0;
}
```
Since 1 is store as `00 01` (in 16b hex form) it would be stored as `00 01` in big endian form and `01 00`. But since we casted the pointer of data to a 8bit pointer it now only points to the first byte. So **`00`** `01` if it's big endian and **`01`** `00` which is small endian. If the value of what the pointer points to is 0<sub>10</sub> (00<sub>16</sub>) it is then big endian and 1<sub>10</sub> (01<sub>16</sub>) small endian. Python is easier :)

There is no immeadiate answer for which is better. What's better milk or cereal first? Most PCs use little endian and most network protocols are big endian. Big endian is often called network endian.

## Assignment 5: Memory Layout
**Q1: Consider AM18, AM19, and AF1. Explain why gv ends up with the incremented value, but m does not.**

A1: gv is a global value so changing it in fun will ofc change its value but when we send a m into fun we send a copy of the data. So we copy the value of m into param change param and then save the increased param not data. 

```mips 
fun:
    move $t0, $a0
    addi $t0, $t0, 1
    sw $t0, 0($sp)
```

**Q2: Pointer cp is a character pointer that points to a sequence of bytes. What is the size of the cp pointer itself?**

A2: 4 bytes = 32 bits (Dependant on word size of cpu)

**Q3: Explain how a C string is laid out in memory. Why does the character string that cp points to have to be 9 bytes?**

A3: There are 8 chars which are each 1 byte and at the end there is a nullbyte \0 which is also 1 byte. This is to indicate the end of the string.

**Q4: Which addresses have fun and main? Which sections are they located in? What kind of memory are they stored in? What is the meaning of the data that these symbols points to?**

fun: 9D001180
main: 9D0011D8

They are both in the program flash according to the reference manual. They are stored in the virual memory map. The data they point to is where the funtion is in memory.

**Before the examination, you should also try to answer the following. When the lab-assistant performs the examination, he/she can also clarify anything that you did not understand with the following questions:**

**Q5: Which addresses are variables in and gv located at? Which memory sections according to the PIC32 memory map? Why?**

in: A000008
gv: A00000C

This is the RAM (random access memory). 

The reason is since it is global it needs to always be accessible and thereby stored in the RAM.

**Q6: Variables p and m are not global variables. Where are they allocated? Which memory section is used for these variables? Why are the address numbers for p and m much larger than for in and gv?**

p: A0003FE8
m: A0003FE4

This is reserved space. They are not global and does not have to be accessed at all times.

**Q7: At print statement AM5, what is the address of pointer p, what is the value of pointer p, and what value is pointer p pointing to?**

A7: 
Address of pointer p: A0003FE8
Value of pointer p: A0003FE4
Value pointer p is pointing to: 7 (AM6)

**Q8: At print statement AM7, what is the address of pointer p, what is the value of pointer p, and what value is pointer p pointing to?**

A8:
Address of pointer p: A0003FE8
Value of pointer p: A0003FE4
Value pointer p is pointing to: 8 (AM8)

**Q9: Consider AM14 to AM17. Is the PIC32 processor using big-endian or little-endian? Why?**

Little endian since`0x1234adcd` is stoed as `cd ab 34 12` in memory. The first byte is the least significant byte and the last byte is the most significant byte.







