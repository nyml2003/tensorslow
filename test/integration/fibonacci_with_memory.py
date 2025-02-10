b = []
n = 20

while len(b) <= n:
    b.append(None)

b[1] = 1
b[2] = 1


def f(x):
    if b[x] is None:
        b[x] = f(x - 1) + f(x - 2)
    return b[x]


print(f(20))
print(b)
