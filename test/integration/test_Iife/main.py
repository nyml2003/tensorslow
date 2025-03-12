a = Matrix.array([[ 1.0,  2.0,  3.0,  4.0],
    [ 5.0,  6.0,  7.0,  8.0],
    [ 9.0, 10.0, 11.0, 12.0]])

print(a)
print(a.shape)
a = Matrix.reshape(a, [2, 6])
print(a)
print(a.shape)
