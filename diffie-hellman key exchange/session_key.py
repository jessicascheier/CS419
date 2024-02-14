def main():
    a = 512
    B = 8183
    p = 23993
    session_key = ((B**a) % p)
    print(session_key)

main()