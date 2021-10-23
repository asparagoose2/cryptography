#include "cryptoUtils.h"
#include <stdio.h>


/*
    Solves the system: x = a mod p , x = b mod q
*/
int Solve_System(int a,int p,int b, int q) {
    int x = 0, y = 0;
    x = inverse(q,p);
    y = inverse(p,q);
    return (a*x*q + b*y*p) % (p*q);
}

int main(int argc, char const *argv[])
{
    printf("%d\n", Solve_System(3,11,1,3));
    return 0;
}
