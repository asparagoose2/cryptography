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

/*
    Given a , n computes a^-1 mod n
*/
int inverse(long long a, long long p) 
{
    int ans = 0;
    int gcd, temp;

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