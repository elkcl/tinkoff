from random import randrange as ra

n = ra(1, 21)
l = ra(0, 10**18+1)
r = ra(l, 10**18+1)
print(n, l, r)

for i in range(n):
    print(ra(1, 10**8+1), ra(1, 10**8+1))
