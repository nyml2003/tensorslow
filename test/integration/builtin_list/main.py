lst = [1, 4, 9, 16, 25]
print(lst)
lst.append(36)
print(lst)
lst.pop()
print(lst)
lst.insert(0, 0)
print(lst)
lst.remove(4)
print(lst)
lst2 = lst.copy()
print(lst2)
lst.clear()
print(lst)
lst = [1, 4, 9, 16, 25]
lst.extend(lst2)
print(lst)

lst3 = [1, "2", "3", "2", 1, "2"]
print(lst3.count("2"))
print(lst3.count(1))

print(lst3.index("2"))
lst3.reverse()
print(lst3)
