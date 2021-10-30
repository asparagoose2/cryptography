#include"cryptoUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

/*
    computes x^e mod m
*/
unsigned int Exponent( unsigned long long x , unsigned long long e , long long m) 
{
    long long exponent = 1;
    unsigned int ans = x%m;
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

int main(int argc, char const *argv[])
{
    time_t t;
    srand((unsigned) time(&t));

    unsigned long long a=0,b=0;
    for(int i=0;i<64;i++)
    {
        a += rand() % (2);
        b += rand() % (2);
        a*= 2;
        b*= 2;
    }
    printf("%d\n", Exponent(2,79,101));
    return 0;
}
