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

int mytime = 0x5957;

volatile int *porte = (volatile int *)0xbf886110;
int count = 0;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr(void)
{
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

  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  delay(1000);

  *porte = count++;

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

  time2string(textstring, mytime);
  display_string(3, textstring);
  display_update();
  tick(&mytime);
  display_image(96, icon);
}
