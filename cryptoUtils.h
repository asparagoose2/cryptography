#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

/*
    given a, b computes gcd (a,b) and m ,n where: ma + nb = gcd(a,b)
*/
void GCD(unsigned long a, unsigned long b, unsigned long *gcd, long *m, long *n)
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

/*
    Given a , n computes a^-1 mod n
*/
int inverse(long long a, long long p) 
{
    long     ans = 0;
    unsigned long gcd, temp;

    GCD(a, p, &gcd, &ans, &temp);

    while(ans < 0) {
        ans += p;
    }
    return ans;
}

/*
    Solves the system: x = a mod p , x = b mod q
*/
int Solve_System(int a,int p,int b, int q) {
    int x = 0, y = 0;
    x = inverse(q,p);
    y = inverse(p,q);
    return (a*x*q + b*y*p) % (p*q);
}



/*
    computes x^e mod m
*/
unsigned long long Exponent( unsigned long long x , unsigned long long e , unsigned long long m) 
{
    unsigned long long exponent = 1;
    unsigned long long ans = x%m;
    unsigned long long tempExponent = e;
    int msbFLAG = 0;
    int index = 1;
    unsigned int exponentArray[64];
    int arraySize = 0;
    
    /*
        convert the exponent to an array representing the number in binary form
    */
    for(int i=0; i < 64; i++ )
    {
        if(tempExponent >> 63) // if we reached the msb start to build the array
        {
            msbFLAG++;
        }
        if(msbFLAG)
        {
            exponentArray[arraySize++] = (tempExponent >> 63); //taking the msb
        }
        tempExponent = tempExponent << 1; // moving to the next digit
    }
    
    while(exponent != e) // square and multiply method
    {
        ans = (ans * ans ) % m;
        exponent *= 2;
        if(exponentArray[index++]) // multiply part (only if the bit is 1)
        {
            ans = (ans * x) % m;
            exponent += 1;
        }
    }
    return ans;
}

unsigned long long recursiveExponent( unsigned long long x , unsigned long long e , unsigned long long m) 
{
    if(x==0)
        return 0;
    if(e==0)
        return 1;
    
    unsigned long long y;


    if(e % 2 == 2)
    {
        y = newExponent(x,e/2,m);
        return (y*y) % m;
    }
    else
    {
        y = x%m;
        return (y * newExponent(x,e-1,m) % m);
    }
}

unsigned long long generate_prime()
{
    unsigned long long primeToReturn = 0;
    do
    {
        primeToReturn =  random_32_bit_number();
    } while(check_primility(primeToReturn) != 1);
    return primeToReturn;
}