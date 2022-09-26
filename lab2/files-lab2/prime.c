/*
 prime.c
 By Marcus Bardvall
 Last modified: 2020-09-15
 This file is in the public domain.
*/

#include <stdio.h>
#include <math.h>

int is_prime(int n)
{
  // check if n is prime
  int i;
  for (i = 2; i <= sqrt(n); i++) // Olle Jernström (sqrt)
  {
    if (n % i == 0)
    {
      return 0;
    }
  }
  return n > 1;
}

int main(void)
{
  printf("%d\n", is_prime(1));   // 1 is not a prime.    Should print 0.
  printf("%d\n", is_prime(11));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
