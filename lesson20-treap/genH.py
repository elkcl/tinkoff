from random import randrange as ra
from random import choice as ch

n = ra(1, 50)
s = set()
print(n)
for i in range(n):
    if len(s) == 0:
        t = 1
    else:
        t = ch([1, 1, 1, 0, 0, 0, -1])
    if t == 1:
        x = ra(0, 100+1)
        s.add(x)
        print('1', x)
    elif t == 0:
        if len(s) == 0:
            continue
        x = ra(1, len(s)+1)
        print('0', x)
    else:
        if len(s) == 0:
            continue
        x = ch(list(s))
        s.remove(x)
        print('-1', x)

