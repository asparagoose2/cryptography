#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


/*
    given a, b computes gcd (a,b) and m ,n where: ma + nb = gcd(a,b)
*/
void GCD(unsigned long a, unsigned long b, unsigned long *gcd, long *m, long *n)
{
    // printf("GCD(%ld,%ld)\n", a, b);
    if (a % b != 0)
    {
        *gcd = a % b;
        GCD(b, (a - ((a / b) * b)), gcd, m, n);
        // printf("m = %ld\n", *m);
        // printf("n = %ld\n", *n);

        int tmp = *n;
        *n = (*m) - ((a / b) * tmp);
        *m = tmp;
        // printf("ans: %lu\n", *m);
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
unsigned long long inverse(unsigned long long a, unsigned long long p) 
{
    unsigned long     ans = 0;
    unsigned long gcd, temp;
    // printf("before GCD in invers ans: %lu\n", ans);
    GCD(a, p, &gcd, &ans, &temp);
    // printf("after GCD in invers ans: %lu\n", ans);

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


unsigned long long Exponent2( unsigned long long x,  unsigned long long H,  unsigned long long n){

	unsigned long long h;
	unsigned long long r;
	int bin[32];
	int i;
	
	r = x;
	i = 0;

	/* Converts H in Binary */
	while( H > 0 ){
		if (H % 2 == 0){
			bin[i] = 0;
		}else{
			bin[i] = 1;
		}
		H = H/2;
		i++;
	}
	i--; //t-1

	while(i>0){

		r = (r * r) % n;
		if( bin[--i] == 1 ){
			r = (r * x) % n;
		}	
	}

	return r;

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
        y = recursiveExponent(x,e/2,m);
        return (y*y) % m;
    }
    else
    {
        y = x%m;
        return (y * recursiveExponent(x,e-1,m) % m);
    }
}

/*
    randomize a 32 bit unsigned long long
    srand nust be initialized
*/
unsigned long random_32_bit_number()
{
    unsigned long toReturn = 1;
    toReturn = toReturn << 1; //changed to make the number smaller
    for(int i=0; i < 30; i++)
    {
        toReturn += rand()%2;
        toReturn = toReturn << 1;
    }
    toReturn += 1; //changed to make the number smaller
    toReturn = toReturn >> 1;
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

unsigned long long generate_prime()
{
    unsigned long long primeToReturn = 0;
    do
    {
        primeToReturn =  random_32_bit_number();
    } while(check_primility(primeToReturn) != 1);
    return primeToReturn;
}
