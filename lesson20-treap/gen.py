from random import randrange as ra
from random import choice as ch

n = ra(1, 3001)
print(n)
for i in range(n):
    print(ch(('+', '?')), ra(0, 10**9+1))
