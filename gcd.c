#include "stdio.h"

/*
    given a, b computes gcd (a,b) and m ,n where: ma + nb = gcd(a,b)
*/
void GCD(int a, int b, int *gcd, int *m, int *n)
{
    if (a % b != 0)
    {
        *gcd = a % b;
        GCD(b, (a - ((a / b) * b)), gcd, m, n);
        int tmp = *n;
        *n = (*m) - ((a / b) * tmp);
        *m = tmp;
    }
    else
    {
        *n = 1;
        *m = 0;
    }
}

int main(int argc, char const *argv[])
{
    int a = 77;
    int b = 5;
    int m , n;
    int ans = 0;
    GCD(a, b, &ans, &m, &n);
    printf("gcd(%d,%d) = %d\n", a, b, ans);
    printf("m * %d + n * %d = (%d,%d)\n", a, b, m,n);
    return 0;
}
