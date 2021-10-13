#include "stdio.h"

void GCD (int a, int b , int* gcd , int* m, int*n)
{
    if(a % b != 0)
    {
        *gcd = a % b;
        GCD(b,(a - ((a/b) * b)),gcd,m,n);
        int tmp = *n;
        *n = (*m) - ((a/b) * tmp);
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
    int a = 324;
    int b = 44;
    int ans = 0;
    GCD(a,b,&ans,&a,&b);
    printf("gcd(%d,%d) = %d\n", a, b, ans);
    return 0;
}
