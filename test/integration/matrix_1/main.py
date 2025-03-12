a = Matrix.eye(3)
print(a)
b = Matrix.array([
    [1.0, 2.0, 3.0],
    [4.0, 5.0, 6.0],
    [7.0, 8.0, 9.0]
])
print(b)
c = Matrix.zeros([3, 3])
print(c)
d = Matrix.ones([3, 3])
print(d)
e = Matrix.diag([1.0, 2.0, 3.0])
print(b)
print(Matrix.transpose(b))
print(b.T)
f = Matrix.array([
    [1.0, 2.0],
    [3.0, 4.0],
    [5.0, 6.0],
    [7.0, 8.0],
    [9.0, 10.0],
    [11.0, 12.0]
])
print(Matrix.reshape(f, [3, 4]))
print(Matrix.reshape(f, [6, 2]))
print(f.shape)
print(Matrix.shape(f))
print(f > 5.0)
print(Matrix.where(f >5.0, 114.0, 514.0))
print(Matrix.concatenate([f,f]))
print(Matrix.ravel(f))
