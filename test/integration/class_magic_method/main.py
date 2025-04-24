class Value:
    def __init__(self, value):
        self.value = value

    def __add__(self, other):
        return Value(self.value + other.value)

    def __str__(self):
        return "Value: " + str(self.value)


v1 = Value(10)
v2 = Value(20)
v3 = v1 + v2
print(v3)
