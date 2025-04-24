class A():
    def __str__(self):
        return "A"


lst = [
    True, False, 1, 0, 0.1, 0.0, None, '', 'abc', [], [1, 2, 3], A()
]

for i in lst:
    print("i =", i)
    print("bool(i) =", bool(i))
    print("not i =", not i)

for i in [True, False]:
    for j in [True, False]:
        print("i =", i, "j =", j)
        print("i and j =", i and j)
        print("i or j =", i or j)
        print("i is j =", i is j)
        print("i is not j =", i is not j)
