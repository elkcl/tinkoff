from sys import argv
from random import randrange as ra
from random import choice as ch
from string import ascii_lowercase as lett

n = ra(1, 10**3 + 1)

s = ''
for i in range(n):
    s += ch(lett)
k = ra(1, 10**18 + 1)

print(s)
print(k)
