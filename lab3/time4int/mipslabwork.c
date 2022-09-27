/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */
#include "time4io.h" /* Declarations for time4io.c */

#define TIMEOUT (80000000 / 256) / 10; // 80Mhz / 10
int timeoutcount = 0;
int prime = 1234567;

int mytime = 0x5957;

volatile int *porte = (volatile int *)0xbf886110;
int count = 0;

char textstring[] = "text, more text, and even more text!";

void btns()
{
  int btns = getbtns();
  // Note: we removed else if so that we can change multiple simultaneously
  if (btns)
  {
    int sw = getsw();
    if ((btns & 0b001) == 1) // first button is pressed
    {
      mytime = mytime & 0xff0f;
      mytime = mytime | (sw << 4);
    }
    if ((btns & 0b010) == 2) // second button is pressed
    {
      mytime = mytime & 0xf0ff;
      mytime = mytime | (sw << 8);
    }
    if ((btns & 0b100) == 4) // third button is pressed
    {
      mytime = mytime & 0x0fff;
      mytime = mytime | (sw << 12);
    }
  }
}

/* Interrupt Service Routine */
void user_isr(void)
{
  // check for interrupt signal
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

  return;
}

/* Lab-specific initialization goes here */
void labinit(void)
{
  // set output
  int bits = ~0b11111111;
  volatile int *trise = (volatile int *)0xbf886100; // 0xbf886100 = TRISE
  *trise &= bits;

  // set output
  int bits_d = 0b111111;
  bits_d = bits_d << 5;
  TRISD |= bits_d;

  // set timer timout 100ms
  T2CON = 0x70;      // 0111 0000 for 1:256
  PR2 = TIMEOUT;     // for a timeout value of 100 ms
  TMR2 = 0x00;       // reset the counter
  T2CONSET = 0x8000; // start the timer

  IEC(0) = 0x100; // enable timer 2 interrupt
  IPC(2) = 0x7;   // set priority to 7
  enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork()
{
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update();
}
