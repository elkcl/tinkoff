from random import randrange

n = randrange(1, 20)
m = randrange(0, 10)
if n == 1:
    m = 0
print(n, m)
for i in range(n):
    print(randrange(1, 10**3), end=' ')
print()
for i in range(m):
    x = randrange(1, n+1)
    y = randrange(1, n+1)
    while x == y:
        y = randrange(1, n+1)
    print(x, y, randrange(1, 10**3))
