#include "cryptoUtils.h"

/*
    randomize a 64 bit unsigned long long
    srand nust be initialized
*/
unsigned long random_32_bit_number()
{
    unsigned long toReturn = 1;
    toReturn = toReturn << 1;
    for(int i=0; i < 30; i++)
    {
        toReturn += rand()%2;
        toReturn = toReturn << 1;
    }
    toReturn += 1;
    return toReturn;
}

/*
    checks if the numner is a prime number with 99.99999% accuracy
    returns 1 if is prime, 0 if not 
*/
int check_primility(unsigned long primeToCheck)
{
    for(int i=0; i<20; i++)
    {
        unsigned long a;
        do
        {
            a = random_32_bit_number();
        } while(a >= primeToCheck);

        unsigned long gcd = 0, t,y;
        GCD(a,primeToCheck,&gcd,&t,&y);
        if(gcd != 1)
        {
            printf("GCD failed! (%d)\n",i);
            return 0;  
        } 

        unsigned long e = (primeToCheck - 1);
        do
        {
            unsigned long exponentAnswer = Exponent(a,e,primeToCheck);
            if( exponentAnswer == -1 || exponentAnswer == (primeToCheck - 1))
            {
                printf("here (%d)\n",i);
                break;
            }
            else if( exponentAnswer == 1)
            {
                e /= 2;
            }
            else 
            {
                printf("exponent failed! (%d) [exponentAnswer: %lu]\n",i, exponentAnswer);
                return 0;
            }
        } while(e % 2 == 0);
    }
    return 1;
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

unsigned long foo(int n, int k)
{
    unsigned long toReturn = 2;
    for(int i =0; i < n - 1; i++)
    {
        toReturn = toReturn * 2;
    }
    return toReturn - k;
}

int main(int argc, char const *argv[])
{
    time_t t;
    srand((unsigned) time(&t));
    unsigned long a,b;
    // a = generate_prime();
    a = foo(32,17);
    printf("a = %lu\n", a);
    printf("exponent : %llu\n",Exponent(2,a-1,a));
    // b = random_64_bit_number();
    if(check_primility(a)) printf("%lu is prime!\n", a);
    else printf("%lu is not a prime", a);
    return 0;
}
