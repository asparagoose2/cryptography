#include "cryptoUtils.h"
#include <stdio.h>

/*
    Given a , n computes a^-1 mod n
*/
int inverse(long long a, long long p) 
{
    int ans = 0;
    int gcd, temp;

    GCD(a, p, &gcd, &ans, &temp);

    ans = ans%p;

    while(ans < 0) {
        ans += p;
    }
    return ans;
}

int main(int argc, char const *argv[])
{
    float a1 = 5;
    int n = 11;
    int a = inverse(a1, n);
    printf("gcd(%lf,%d) = %d\n", a1, n, a);
    return 0;
}
