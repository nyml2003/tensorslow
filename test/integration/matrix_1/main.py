a = Eye(3)
print(a)
b = Array([
    [1.0, 2.0, 3.0],
    [4.0, 5.0, 6.0],
    [7.0, 8.0, 9.0]
])
print(b)
c = Zeros([3, 3])
print(c)
d = Ones([3, 3])
print(d)
e = Diag([1.0, 2.0, 3.0])
print(b)
print(Transpose(b))
print(b.T)
f = Array([
    [1.0, 2.0],
    [3.0, 4.0],
    [5.0, 6.0],
    [7.0, 8.0],
    [9.0, 10.0],
    [11.0, 12.0]
])
print(Reshape(f, [3, 4]))
print(Reshape(f, [6, 2]))
print(f.shape)
print(Shape(f))
print(f > 5.0)
print(Where(f > 5.0, 114.0, 514.0))
print(Concatenate([f, f]))
print(Ravel(f))
