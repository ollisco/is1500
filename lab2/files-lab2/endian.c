#include <inttypes.h>
#include <stdio.h>
int main(void)
{
    uint16_t data = 1; // two bytes
    uint8_t *ptr;      // one byte

    ptr = (uint8_t *)&data; // cast the address of data to a pointer to a byte
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