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