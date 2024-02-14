#!/usr/bin/python3
import sys

# important info on running the stream cipher:
    # python3 scrypt.py password plaintext ciphertext
    # python3 scrypt.py password ciphertext plaintext

    # password is a text string
    # plaintext and ciphertext are files
    # The same program can be used to encrypt or decrypt.
    # Your program should handle data of any size (e.g., gigabytes).
    # As such, it’s not a good idea to read the entire file into memory a priori.

def sbdm(str):
    hash = 0
    for c in str:
        hash = ord(c) + (hash << 6) + (hash << 16) - hash
    return hash

def main():
    # implement a linear congruential generator (pseudorandom number generator)
    # formula:
    # Xn+1 = [(a * Xn) + (c mod m)]

    m = 256 # modulus
    a = 1103515245 # multiplier
    c = 12345 # increment

    # convert the password to a seed
    password = sys.argv[1]
    # use the sbdm hash function 
    seed = sbdm(password)

    first_filename = sys.argv[2]
    second_filename = sys.argv[3]

    with open(first_filename, 'rb') as first_file:
        first = first_file.read()

    # apply the stream cipher
    Xn = seed

    with open(second_filename, 'wb') as second_file:
        for byte in first:
            keystream_byte = (a * Xn + c) % m
            # xor byte of first file with keystream byte to get ciphertext byte
            second_file_byte = byte ^ keystream_byte
            second_file.write(bytes([second_file_byte]))
            # update Xn
            Xn = keystream_byte


main()