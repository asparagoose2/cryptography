import codecs

def init(key):
    key_length = len(key)
    S = list(range(256))
    j = 0
    for i in range(256):
        j = (j + S[i] + key[i % key_length]) % 256
        S[i], S[j] = S[j], S[i]

    i = 0
    j = 0
    while True:
        i = (i + 1) % 256
        j = (j + S[i]) % 256

        S[i], S[j] = S[j], S[i]  # swap values
        K = S[(S[i] + S[j]) % 256]
        yield K

def encrypt(key, message):
    key = [ord(c) for c in key]
    text = [ord(c) for c in message]
    keystream = init(key)

    res = []
    for c in text:
        val = ("%02X" % (c ^ next(keystream)))
        res.append(val)
    return ''.join(res)

def decrypt(key, ciphertext):
    ciphertext = codecs.decode(ciphertext, 'hex_codec')
    key = [ord(c) for c in key]
    keystream = init(key)

    res = []
    for c in ciphertext:
        val = ("%02X" % (c ^ next(keystream)))
        res.append(val)
    return codecs.decode(''.join(res), 'hex_codec').decode('utf-8')
    


def main():
    key = '1111'
    plaintext = 'This is the message we want to keep a secret!'
    ciphertext = encrypt(key, plaintext)
    print('plaintext:', plaintext)
    print('ciphertext:', ciphertext)
    decrypted = decrypt(key, ciphertext)
    print('decrypted:', decrypted)

    if plaintext == decrypted:
        print('\nCiphertext decrypted successfully.')
    else:
        print('\nCiphertext decryption failed.')


if __name__ == '__main__':
    main()
