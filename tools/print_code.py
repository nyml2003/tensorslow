import marshal
import struct
import dis
import sys


def inspect_code(code, indent=0):
    """
    递归检查代码对象的详细信息
    """
    print("\n" + "  " * indent + "--- Code Object Details ---")
    print("  " * indent + f"consts: {code.co_consts}")
    print("  " * indent + f"names: {code.co_names}")
    print("  " * indent + f"varnames: {code.co_varnames}")
    print("  " * indent + f"filename: {code.co_filename}")
    print("  " * indent + f"name: {code.co_name}")
    print("  " * indent + f"nlocals: {code.co_nlocals}")
    print("  " * indent + f"cellvars: {code.co_cellvars}")
    print("  " * indent + f"freevars: {code.co_freevars}")
    print("  " * indent + "bytecode:")
    # 打印字节码，但是不用递归
    dis.dis(code)

    # 如果代码对象中包含嵌套的代码对象（如函数或类），递归检查
    for const in code.co_consts:
        if isinstance(const, type(code)):
            inspect_code(const, indent + 1)

def compile_and_inspect_py(file_path):
    """
    接受一个 Python 文件路径，编译为代码对象并打印字节码
    """
    try:
        # 读取 Python 文件内容
        with open(file_path, "r") as f:
            source_code = f.read()
        
        # 编译代码为代码对象
        code_obj = compile(source_code, file_path, mode="exec")
    
        
        # 递归检查代码对象的详细信息
        inspect_code(code_obj)
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
    except SyntaxError as e:
        print(f"Syntax Error in file '{file_path}': {e}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <file_path>")
    else:
        file_path = sys.argv[1]
        compile_and_inspect_py(file_path)