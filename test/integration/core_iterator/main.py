for x in [1,2,3,4]:
    print (x)


class MyNumbers:
    def __iter__(self):
        self.a = 1
        return self

    def __next__(self):
        x = self.a
        self.a += 1
        return x

myclass = MyNumbers()
myiter = iter(myclass)

print(next(myiter))
print(next(myiter))
print(next(myiter))
print(next(myiter))
print(next(myiter))

def countdown(n):
    while n > 0:
        yield n
        n -= 1

# 创建生成器对象
generator = countdown(5)

# 通过迭代生成器获取值
print(next(generator))  # 输出: 5
print(next(generator))  # 输出: 4
print(next(generator))  # 输出: 3

# 使用 for 循环迭代生成器
for value in generator:
    print(value)  # 输出: 2 1

def range(start, end, step):
    if step == 0 or step is None:
        step = 1
    if end is None:
        end = start
        start = 0
    if step > 0:
        while start < end:
            yield start
            start += step
    else:
        while start > end:
            yield start
            start += step

a = [1, 2, 3, 4, 5]

for i in range(len(a)):
    print(a[i])
