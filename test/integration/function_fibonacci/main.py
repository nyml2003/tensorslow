n = 20
b = [1, 1] + [None] * n


def f(x):
    if b[x] is None:
        b[x] = f(x - 1) + f(x - 2)
    return b[x]


print(f(20))
print(b)

# init = Array([[1.0], [1.0]])
# transform = Array([[1.0, 1.0], [1.0, 0.0]])
# n = 19
# transform = transform ** n
# ans = transform @ init
# print(ans[1, 0])
