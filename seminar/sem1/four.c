

#include <stdio.h>

int main()
{
    int n, k;
    int c = 0x02524827;

    printf("%d\n", c);
    for (c = 31; c >= 0; c--)
    {
        k = n >> c;

        if (k & 1)
            printf("1");
        else
            printf("0");
    }

    printf("\n");
    return 0;
}

/*----------------------------------------------------------------
Which is 0b00000100100110111000000001100000
the first bytes 000010 = 2 in decimal
Therefore, two is the op code.
The instruciton whit 2 as op code is jump.

The rest of the bytes {0100110111000000001100000} is the address.
----------------------------------------------------------------*/
