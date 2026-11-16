import random


def password_generator():
    # These strings contain the character types used to make passwords.
    uppercase_letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    lowercase_letter = "abcdefghijklmnopqrstuvwxyz"
    digit = "0123456789"
    symbols = "!@#$%^&*()_+{}\\|?/<>-,.;:[]'= "

    # These options decide which character types are added to the pool.
    use_uppercase = True
    use_lowercase = True
    use_digit = True
    use_symbols = True

    # This combines the enabled character types into one pool.
    character_pool = ""
    if use_uppercase:
        character_pool += uppercase_letter
    if use_lowercase:
        character_pool += lowercase_letter
    if use_digit:
        character_pool += digit
    if use_symbols:
        character_pool += symbols

    # This asks how long each password should be and how many to make.
    length = int(input("Enter the length of the password: "))
    amount = int(input("Enter the number of passwords to generate: "))

    # This makes sure the requested passwords can be made from the pool.
    if length < 1 or amount < 1:
        print("Enter positive numbers for the length and amount.")
        return
    if length > len(character_pool):
        print(f"Password length cannot exceed {len(character_pool)} characters.")
        return

    for _ in range(amount):
        # This picks characters without repeating any within one password.
        password = "".join(random.sample(character_pool, length))
        print(password)


