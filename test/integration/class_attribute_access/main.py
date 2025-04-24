class MyClass:
    def __init__(self, value):
        self.value = value

    def display_value(self):
        print(self.value)


# 创建一个类的实例
obj = MyClass(42)

# 调用实例的方法
obj.display_value()  # 输出 42

obj.add_func = obj.display_value

obj.add_func()


def add_func2(self):
    print("This is a function added to the class instance.", self.value)


obj.add_func2 = add_func2

obj.add_func2(obj)
