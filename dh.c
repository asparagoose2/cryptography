#include "cryptoUtils.h"

unsigned long long private_key;
unsigned long long public_key;

// This function sets the private and public keys which are global variables
unsigned long long generate_keyPair(int p , int alpha)
{
    private_key = rand()%p;
    public_key = Exponent(alpha, private_key, p);
    printf("Private key: %llu\n", private_key);
    printf("Public key: %llu\n\n", public_key);
    return public_key;
}

void DH_encrypt(unsigned long long p , int alpha, unsigned long long Kpub , unsigned long message, unsigned long long* ephemeral_key, unsigned long*  cipher)
{
    unsigned long long i = (rand()%(p-4))+2;
    *ephemeral_key = Exponent(alpha, i, p);
    unsigned long long Km = Exponent(Kpub, i, p);
    *cipher = (message * Km) % p;
}

void DH_decrypt(unsigned long long p , int alpha, unsigned long long Keph , unsigned long cipher, unsigned long* message) 
{
    unsigned long long Km = Exponent(Keph, private_key, p); 
    *message = (cipher * inverse(Km, p)) % p;
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));

    unsigned long chipher;
    unsigned long message = 12789;
    unsigned long decryptedMessage;
    unsigned long long ephemeral_key;
    unsigned long long p = generate_prime();
    printf("p = %llu\n", p);
    DH_encrypt(p, 2, generate_keyPair(p,2),message, &ephemeral_key, &chipher);
    printf("Original message = %ld\n", message);
    printf("chipher = %ld\n", chipher);
    DH_decrypt(p, 2, ephemeral_key, chipher, &decryptedMessage);
    printf("Decrypted Message: %ld\n", decryptedMessage);
}