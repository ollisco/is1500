#include <stdio.h>

int square_revese(double *x, double *y, int len)
{
    double sum = 0;
    int i;
    double t;
    for (i = 0; i < len; i++)
    {
        t = x[len - i - 1];
        y[i] = t * t;
        sum += t;
    }
    return sum;
}

int main()
{
    int n = 3;
    double in[] = {-11.0, 20.0, 100.0};
    double out[n];
    double sum = square_revese(in, out, n);
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%f \n", out[i]);
    }

    printf("sum: %f \n", sum);
    return 0;
}