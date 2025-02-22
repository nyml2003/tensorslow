def range(start, end):
    step = 1
    lst = []
    if start < end and step > 0:
        while start < end:
            lst.append(start)
            start = start + step
    return lst


for i in range(1, 10):
    cur = ""
    for j in range(1, i + 1):
        cur = cur + str(j) + "×" + str(i) + "=" + str(i * j) + "  "
    print(cur)