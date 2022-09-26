/*
 print-prime.c
 By Marcus Bardvall
 Last modified: 2022-09-15
 This file is in the public domain.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6
int current = 0;

int is_prime(int n)
{
    // check if n is prime
    int i;
    for (i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return n > 1;
}

void print_number(int n)
{
    if (current == COLUMNS)
    {
        printf("\n");
        current = 0;
    }
    printf("%d ", n);
    current++;
}

void print_prime_index(int n)
{
    int checked_primes = 0;
    int i = 2;
    while (1)
    {
        if (is_prime(i))
        {
            checked_primes++;
            if (checked_primes == n)
            {
                print_number(i);
                return;
            }
        }
        i++;
    }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[])
{
    if (argc == 2)
        print_prime_index(atoi(argv[1]));
    else
        printf("Please state an interger number.\n");
    return 0;
}
