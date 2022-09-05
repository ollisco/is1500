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

A2: sieves.c and sieves-heap.c are both able to print all numbers before seg fault in the two second window. print primes does not have to allocate all memory at once and can go further even though it is slower.
 


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

A5: M1 MacBook has two CPU architecures. Intel x86 and ARM. Both of these use little endian though. From experience the way this can be checked is using this python snippet.

Python:
```python
from sys import byteorder
print(byteorder) # will print 'little' or 'big'
```

Which can also be done in C 
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

