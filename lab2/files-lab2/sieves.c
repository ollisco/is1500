/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
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

    return 1;
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

void print_sieves(int n)

{
    // generate array
    int array[n - 1];
    for (int i = 0; i < n - 1; i++)
    {
        array[i] = i + 2;
    }

    // sieves
    int i;
    for (i = 0; i <= sqrt(n); i++)
    {
        int v = array[i];
        if (v)
        {
            for (int j = v * v; j <= n; j += v)
            {
                array[j - 2] = 0;
            }
        }
    }

    // print array items != 0
    for (int i = 0; i < n - 1; i++)
    {
        if (array[i])
        {
            print_number(array[i]);
        }
    }
    printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[])
{
    if (argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an interger number.\n");
    return 0;
}
