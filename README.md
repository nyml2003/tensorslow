# Tensorslow 项目

Tensorslow 是一个用C++实现的Python解释器和编译器框架，包含机器学习功能支持。

🎉 My first one-year-long and 10k-line-code project!

## 快速体验

[tensorslow演示](https://ventusvocatflumen.cn/compile/)

## 项目结构

```text
tensorslow/
├── cmake/            # CMake构建配置
├── src/              # 源代码目录
│   ├── Backend/      # 解释器后端
│   ├── ByteCode/     # 字节码相关
│   ├── Collections/  # 集合类型实现
│   ├── Engine/       # 聚合入口
│   ├── Frontend/     # 编译器前端
│   ├── Function/     # 函数相关
│   ├── Generation/   # 中间代码生成
│   ├── IR/           # 中间代码
│   ├── Object/       # 对象系统
│   ├── Runtime/      # 运行时
│   ├── Tools/        # 工具类
│   ├── Common.h      # 公共定义
│   └── source.cmake  # 源代码CMake配置
├── grammar/          # ANTLR语法文件
├── test/             # 测试代码
└── tools/            # 工具脚本
```

## 主要模块

1. **Tensorslow Compiler** - 将Python代码编译为字节码
2. **Tensorslow Interpreter** - 执行Python代码

## 构建说明

### 依赖项

- CMake 3.20+
- ANTLR4
- C++17兼容编译器
- java

### 构建步骤

```bash
python tools/build.py
```

构建目标:

- tensorslow_compiler
- tensorslow_interpreter
- tensorslow_engine

## 使用示例

### 选项

| 选项 | 默认值 | 描述 |
| --- | --- | --- |
| --compile | true | 是否编译成字节码 |
| --file |  | 单文件模式，指定要解析的文件 |
| --interpret | true | 是否直接解释执行源代码 |
| --interpret_bytecode | true | 是否解释执行字节码 |
| --show_ast | true | 是否显示抽象语法树 |
| --show_bc | true | 是否显示生成的code object |
| --show_ir | true | 是否显示中间代码树 |
| --show_result | true | 是否直接输出结果 |
| --show_tokens | true | 是否显示词法分析结果 |
| --source |  | 字符串模式，指定要解析的源代码字符串 |
| --verbose | true | 开启调试模式，逐指令打印栈帧 |
| --help |  | 显示帮助信息 |
| --version |  | 显示版本信息 |

### 示例

以源码模式启动引擎，并直接解释执行源代码:

```bash
build/Release/tensorslow_engine.exe --source="
def f(a,b):
    return a+b
print(f(114,514))
" --interpret
```

结果为

```bash
628
```

## 开发工具

项目提供了一些有用的开发工具:

- `tools/integration.py` - 集成测试工具
- `tools/build.py` - 构建辅助工具
- `tools/integration_ml.py` - 机器学习集成测试

## 语法特性支持

### 运算符示例

```bash
build/Release/tensorslow_engine.exe --source="
a = 10
b = 3
print(a + b, a - b, a * b, a / b, a // b, a % b, a ** b)
" --interpret
```

结果为

```bash
13 7 30 3.333333 3 1 1000
```

### 控制流语句示例

```bash
build/Release/tensorslow_engine.exe --source="
x = 10
if x > 5:
    print('x > 5')
else:
    print('x <= 5')
for i in range(3):
    print(i)
" --interpret
```

结果为

```bash
x > 5
0
1
2
```

### 基本数据类型示例

```bash
build/Release/tensorslow_engine.exe --source="
num = 42
pi = 3.14
name = 'Tensorslow'
nums = [1, 2, 3]
info = {'name': 'Alice', 'age': 20}
flag = True
print(type(num), type(pi), type(name), type(nums), type(info), type(flag))
" --interpret
```

结果为

```bash
<class 'int'> <class 'float'> <class 'str'> <class 'list'> <class 'dict'> <class 'bool'>
```

### 函数示例

```bash
build/Release/tensorslow_engine.exe --source="
def greet(name):
    return 'Hello, ' + name + '!'
print(greet('World'))
print(len([1, 2, 3]))
" --interpret
```

结果为

```bash
Hello, World!
3
```

### 面向对象示例

```bash
build/Release/tensorslow_engine.exe --source="
class Animal:
    def speak(self):
       print('Animal speaks')
class Dog(Animal):
    def speak(self):
        print('Dog barks')
class Cat(Animal):
    def speak(self):
        print('Cat meows')
animal = Animal()
animal.speak()
dog = Dog()
dog.speak()
cat = Cat()
cat.speak()
" --interpret
```

结果为

```bash
Animal speaks
Dog barks
Cat meows
```

### 迭代器示例

```bash
build/Release/tensorslow_engine.exe --source="
def my_range(_start, _end, _step):
    i = _start
    while i < _end:
        yield i
        i += _step
for i in my_range(0, 10, 2):
    print(i)
" --interpret
```

结果为

```bash
0
2
4
6
8
```

### 切片示例

```bash
build/Release/tensorslow_engine.exe --source="
lst = [0, 1, 2, 3, 4, 5]
print(lst[1:4])
print(lst[::2])
print(lst[::-1])
" --interpret
```

结果为

```bash
[1, 2, 3]
[0, 2, 4]
[5, 4, 3, 2, 1, 0]
```

## 机器学习支持

- 损失函数
  - 感知机损失函数
  - 对数损失函数
  - 交叉熵损失函数
- 优化器
  - 梯度下降优化器
  - 动量优化器

## Copyright

打印全局常量whoami

```bash
build/Release/tensorslow_engine.exe --source="
print(whoami)
" --interpret
```

```bash
版权所有 © 2025 蒋钦禹. 保留所有权利。
```
