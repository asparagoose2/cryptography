import random
def gcd(a,b):
    """
    Returns a tuple (r, i, j) such that r = gcd(a, b) = ia + jb.
    """
    # Set our initial values.
    x = y = 0
    u = 1
    v = 0
    # While our remainder is not zero.
    while b != 0:
        # Calculate the next values.
        q = a // b
        a, b = b, a % b
        x, u = u - q*x, x
        y, v = v - q*y, y
    return (a, u, v)

def is_prime(number):
    """
    Returns True if n is prime, False otherwise.
    """
    # Check if n is not even.
    if number % 2 == 0:
        return False
    #loop 20 times to insure that the number is prime.
    for i in range(20):
        # Generate a random number between 2 and n-2.
        a = random.randint(2, number-2)
        # Check if a^(n-1) = 1 (mod n).
        if square_and_multiply(a, number-1, number) != 1:
            return False
    return True

def square_and_multiply(a, b, n):
    """
    Returns a^b mod(n).
    """
    result = 1
    while b > 0:
        # If b is odd, multiply result by a.
        if b & 1:
            result = (result * a) % n
        # Square a.
        a = (a * a) % n
        # Divide b by 2.
        b >>= 1
    return result

def generate_prime_number(bits):
    """
    Generates a prime number of the given size.
    """
    # Generate a random number.
    random_number = random.randint(0, 2**(bits-1))
    # Make sure it's odd.
    random_number |= 1
    # Keep generating until a prime is found.
    while not is_prime(random_number):
        random_number = random.randint(0, 2**(bits-1))
        random_number |= 1
    return random_number

class Rsa:
    def __init__(self):
        self.public_key, self.private_key = self.generate_key_pair()

    def encrypt(self,message):
        """
        Encrypts a message using a public key.
        """
        # Get the public key.
        e, n = self.public_key
        # Encrypt the message.
        return square_and_multiply(message, e, n)

    def decrypt(self, cipher):
        """
        Decrypts a cipher using a private key.
        """
        # Get the private key.
        d, n = self.private_key
        # Decrypt the cipher.
        return square_and_multiply(cipher, d, n)

    def get_public_key(self):
        """
        Returns the public key.
        """
        return self.public_key

    def generate_key_pair(self):
        """
        Generates a public and private key pair.
        Returns a tuple (public_key), (private_key).
        """
        # Generate 2 prime numbers.
        p = generate_prime_number(64)
        q = generate_prime_number(64)

        # Calculate n = pq.
        n = p * q
        # Calculate phi(n) = (p-1)(q-1).
        phi = (p-1) * (q-1)
        # Choose a random number e.
        e = random.randint(1, phi)
        # Find the greatest common divisor of e and phi(n).
        gcd_result = gcd(e, phi)
        # Check if gcd(e, phi(n)) = 1.
        while gcd_result[0] != 1:
            # Choose another e.
            e = random.randint(1, phi)
            # Find the greatest common divisor of e and phi(n).
            gcd_result = gcd(e, phi)
        # Calculate d = e^-1 mod(phi(n)).
        d = gcd_result[1] % phi
        # Return the public and private key.
        return (e, n), (d, n)


if __name__ == "__main__":
    rsa = Rsa()
    # Generate a public and private key.
    # public_key, private_key = generate_key_pair()
    message = 12345678987654321
    # Encrypt a message.
    cipher = rsa.encrypt(message)
    # Decrypt the message.
    decrypted_message = rsa.decrypt(cipher)
    # Print the results.
    print("Original message:", message)
    print("Encrypted message:", cipher)
    print("Decrypted message:", decrypted_message)
    print("Success? ", message == decrypted_message)

