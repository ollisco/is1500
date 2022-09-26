# LAB 3

## Assignment 1: Polling switches

**Q1 Test pressing BTN3 and BTN2 at the same time. What happens? Why?**

Both the second and the third button (from the right) are changed at the same time. This is because we check each button individually.

**Q2: Three device-registers for input/output control are TRISE, TRISESET, and TRISECLR. Their functions are related. How? What are the differences?**


TRISx (TRISE) tells if the given port is a input (1) or output (0).
TRISxSET sets the bit in the given port to the given value (index).
TRISxCLR clears the bit in the given port to the given value (index).

They are related since the operate on same port.

**Q3: In the generated assembly code, in which MIPS register will the return values from functions getbtns and getsw be placed in. You should be able to answer this question without debugging the generated assembly code.**

Both in v0. (Saved separately)


**Q4: In this exercise, we explained which bits that should be used in Port D and Port E. How can you find this information in the PIC32 and ChipKIT manuals? Be prepared to demonstrate how to find this information in the manuals. Advice: check the lecture slides from lecture 5 for ideas**

I/O Ports section 12. Chipkit manual (Literature section at canvas)

Lecture 5 slides on canvas.

PIC 32 is installed.

## Assignment 2: Timer











