def fibonacci(a):
    if a == 1:
        return 1
    if a == 2:
        return 1
    return fibonacci(a - 1) + fibonacci(a - 2)

print(fibonacci(20))
