#include "cryptoUtils.h"

/*
    randomize a 32 bit unsigned long long
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
            return 0;  
        } 

        unsigned long e = (primeToCheck - 1);
        do
        {
            unsigned long exponentAnswer = Exponent(a,e,primeToCheck);
            if( exponentAnswer == -1 || exponentAnswer == (primeToCheck - 1))
            {
                break;
            }
            else if( exponentAnswer == 1)
            {
                e /= 2;
            }
            else 
            {
                return 0;
            }
        } while(e % 2 == 0);
    }
    return 1;
}

unsigned long long generate_prime(int* numberOfTries)
{
    unsigned long long primeToReturn = 0;
    *numberOfTries = 0;
    do
    {
        (*numberOfTries)++;
        primeToReturn =  random_32_bit_number();
    } while(check_primility(primeToReturn) != 1);
    printf("Number of tries: %d\n", *numberOfTries);
    printf("primeNumber = %llu\n", primeToReturn);
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
    unsigned long primeNumber,randomNumber;
    //loop to generate prime numbers 10 times and calculates the average number of tries
    int averageNumberOfTries = 0, numberOfTries = 0;
    for(int i = 0; i < 10; i++)
    {
        generate_prime(&numberOfTries);
        averageNumberOfTries += numberOfTries;
    }
    averageNumberOfTries /= 10;
    printf("\n\nAverage number of tries: %d\n", averageNumberOfTries);
    // primeNumber = generate_prime(&numberOfTries);
    // a = foo(32,209); calculates prime number 2^n - k
    // if(check_primility(primeNumber)) 
    // {
    //     printf("%lu is prime!\n", primeNumber);
    // }
    // else
    // {
    //     printf("%lu is not prime!\n", primeNumber);
    // }
    // randomNumber = random_32_bit_number();
    // printf("randomNumber = %lu\n", randomNumber);
    // if(check_primility(randomNumber)) 
    // {
    //     printf("%lu is prime!\n", randomNumber);
    // }
    // else
    // {
    //     printf("%lu is not prime!\n", randomNumber);
    // }
    return 0;
}
