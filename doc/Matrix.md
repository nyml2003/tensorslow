# ApiName
matrix.eye(n)
# Description
n×n 单位矩阵
# Parameter
n: int
# Return
n×n 单位矩阵

# Example
```python
>>> eye(3)
[[1, 0, 0], [0, 1, 0], [0, 0, 1]]
```

# ApiName
matrix.zeros(n, m)
# Description
n×m 全零矩阵
# Parameter
n: int
m: int
# Return
n×m 全零矩阵

# Example
```python
>>> zeros(2, 3)
[[0, 0, 0], [0, 0, 0]]
```

# ApiName
matrix.ones(n, m)
# Description
n×m 全一矩阵
# Parameter
n: int
m: int
# Return
n×m 全一矩阵

# Example
```python
>>> ones(2, 3)
[[1, 1, 1], [1, 1, 1]]
```

# ApiName
matrix.rand(n, m)
# Description
n×m 随机矩阵
# Parameter
n: int
m: int
# Return
n×m 随机矩阵

# Example
```python
>>> rand(2, 3)
[[0.1, 0.2, 0.3], [0.4, 0.5, 0.6]]
```

# ApiName
matrix.diag(v)
# Description
对角矩阵
# Parameter
v: List
# Return
对角矩阵

# Example
```python
>>> diag([1, 2, 3])
[[1, 0, 0], [0, 2, 0], [0, 0, 3]]
```

# ApiName
matrix.transpose(m)
# Description
矩阵转置
# Parameter
m: List
# Return
转置矩阵

# Example
```python
>>> transpose([[1, 2], [3, 4], [5, 6]])
[[1, 3, 5], [2, 4, 6]]
```


