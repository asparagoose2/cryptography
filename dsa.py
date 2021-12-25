import random
import hashlib


def gcd(a, b):
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
    # loop 20 times to insure that the number is prime.
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

def inverse(a, n):
    """
    Returns the inverse of a mod(n).
    """
    # Calculate the gcd.
    gcd_result = gcd(a, n)
    # Check if a and n are co-prime.
    if gcd_result[0] != 1:
        return None
    # Calculate the inverse.
    return gcd_result[1] % n

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


class Dsa:
    def generate_keypair(self, p, q, alpha):
        """
        Generates a public and private key pair.
        """
        self.p = p
        self.q = q
        self.alpha = alpha
        self.d = random.randint(1, q-1)
        self.beta = square_and_multiply(alpha, self.d, p)
        self.public_key = (self.p, self.q, self.alpha, self.beta)
        return self.public_key

    def sign(self, message):
        """
        Signs a message using a private key.
        """
        Ke = random.randint(1, self.q-1)
        r = square_and_multiply(self.alpha, Ke, self.p) % self.q
        hash = hashlib.sha256()
        hash.update(str(message).encode('utf-8'))
        sha = int(hash.hexdigest(), 16)
        s = ((sha + self.d*r) * inverse(Ke, self.q)) % self.q
        return (r, s)

    def verify(self, message, signature):
        """
        Verifies a signature using a public key.
        """
        r, s = signature
        hash = hashlib.sha256()
        hash.update(str(message).encode('utf-8'))
        sha = int(hash.hexdigest(), 16)
        w = inverse(s, self.q)
        u1 = (sha * w) % self.q
        u2 = (r * w) % self.q
        v = ((square_and_multiply(self.alpha, u1, self.p) * square_and_multiply(self.beta, u2, self.p)) % self.p) % self.q
        return v == r

if __name__ == "__main__":
    dsa = Dsa()
    p = 59
    q = 29
    alpha = 3
    public_key = dsa.generate_keypair(p, q, alpha)
    message = "this is my message"
    signature = dsa.sign(message)
    print(dsa.verify("this is my message", signature))
    print(dsa.verify("this ist my message", signature))



