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

Both in v0. 

<!-- (Saved separately) -->


**Q4: In this exercise, we explained which bits that should be used in Port D and Port E. How can you find this information in the PIC32 and ChipKIT manuals? Be prepared to demonstrate how to find this information in the manuals. Advice: check the lecture slides from lecture 5 for ideas**

I/O Ports section 12. Chipkit manual (Literature section at canvas)

Lecture 5 slides on canvas.

PIC 32 is installed.

## Assignment 2: Timer
**Q1: When the time-out event-flag is a "1", how does your code reset it to "0"?**
```c
IFSCLR(0) = 0x100;
```


**Q2: What would happen if the time-out event-flag was not reset to "0" by your code? Why?**
It would not delay the program after the first flag is set.

**Q3: Which device-register (or registers) must be written to define the time between time-out events? Describe the function of that register (or of those registers).**

TMR2

**Q4: • If you press BTN3 quickly, does the time update reliably? Why, or why not? If not, would that be easy to change? If so, how?**

No since we update every second it will wait until the next update event which can take 0-1 second. This can be changed by updating the timer value every time we press the button. Although we want to do every thing in the timer since we do not want to speed up the clock.


## Assignment 3: Interrupts
**When the time-out event-flag is a "1", how does your code reset it to "0"?**
 
```c
 if (IFS(0) & 0x100)
  {
    // reset interrupt signal
    IFSCLR(0) = 0x100; // THIS LINE RESETS THE FLAG
    // increment timeoutcount
    timeoutcount++;
    // check if timeoutcount is 10
    if (timeoutcount == 10)
    {
      time2string(textstring, mytime);
      display_string(3, textstring);
      display_update();
      tick(&mytime);
      // reset timeoutcount
      timeoutcount = 0;
      // increment mytime
      mytime++;
    }
  }
```

**What would happen if the time-out event-flag was not reset to "0" by your code? Why?**
Then the update statement would run every time since every period the interrupt 1 is overwritten with 1.

**From which part of the code is the function user_isr called? Why is it called from there?**
In vectors.S since there is where the interrupt handler is.

**Why are registers saved before the call to user_isr? Why are only some registers saved?**
To ensure that the values are the same after the interrupt handler is done. Only some are saved since the S registers are already saved.

**Which device-register (or registers), and which processor-register (or registers) must be written to enable interrupts from the timer? Describe the functions of the relevant registers.**
```c
// T2IE - Device register
IEC(0) = 0x100; // enable timer 2 interrupt
```
"The k registers are reserved for use by the OS kernel. They may change randomly at any time as they are used by interrupt handlers." - Wikipedia.











