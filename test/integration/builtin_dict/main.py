#!/usr/bin/python3

# 初始化字典
tinydict = {'Name': '风唤长河', 'Age': 7, 'Class': 'First'}

# 测试用例1：访问字典的值
print("tinydict['Name']: ", tinydict['Name'])
print("tinydict['Age']: ", tinydict['Age'])

# 测试用例2：重复键名会被覆盖
tinydict = {'Name': '风唤长河', 'Age': 7, 'Name': '蒋钦禹'}
print("tinydict['Name']: ", tinydict['Name'])

# 测试用例3：更新和添加字典的值
tinydict['Age'] = 8  # 更新 Age
tinydict['School'] = "电子科技大学"  # 添加信息
print("tinydict['Age']: ", tinydict['Age'])
print("tinydict['School']: ", tinydict['School'])
