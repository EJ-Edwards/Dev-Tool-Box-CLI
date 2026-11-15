import random

uppercase_letter = "ABCDEFGHIJKLMNOPQRSTVWXYZ"
lowercase_letter = "abcdefghijklmnopqrstuvwxyz"
digit = "1234567890"
symbols = "!@#$%^&*()_+}{}\|?/<>-,.;:[]'= "

use_uppercase = True
use_lowercase = True
use_digit = True
use_symbols = True

all = ""

if uppercase_letter:
    all += uppercase_letter

if lowercase_letter:
    all += lowercase_letter

if digit:
    all += digit

if symbols:
    all +=  symbols

length = 20
ammount = 30

for x in range(ammount):
    password = "".join(random.sample(all, length)) 
    print(password)


