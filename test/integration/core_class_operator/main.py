class Value:
    def __init__(self, value):
        self.value = value

    def __add__(self, other):
        return self.value + other.value

a = Value(1)
b = Value(2)
print(a + b)
