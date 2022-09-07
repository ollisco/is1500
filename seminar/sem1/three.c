#include <stdio.h>

void subber(const int *x, const int *y, int *z)
{
    *z = *x - *y;
}

int foo(int a)
{
    const int k = 10;
    int r = 0;
    subber(&a, &k, &r);
    return r;
}

int main()
{
    const int x = 5;
    const int y = 2;
    int z;
    subber(&x, &y, &z);
    // print x,y,z
    printf("x = %d, y = %d, z = %d", x, y, z);
    // print foo(x)
    printf("foo(%d) = %d", 7, foo(7));
}