# 设置工作目录
set(tensorslow_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(tensorslow_src_dir ${tensorslow_dir}/src)

# 设置 C++ 标准和编译器选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(tensorslow_cxx_flags)

# 无视warning
if (MSVC)
    list(APPEND CMAKE_CXX_FLAGS /W0)
else()
    # list(APPEND CMAKE_CXX_FLAGS -w)
endif()
## 针对当前 CPU 的指令集优化
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native")
#
#
## 向量化和数学优化
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffast-math -ftree-vectorize")
#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffast-math -ftree-vectorize")
#
if(MSVC)
    list(APPEND tensorslow_cxx_flags /utf-8)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-finput-charset=UTF-8)
endif()
list(APPEND tensorslow_cxx_flags -fcolor-diagnostics)
list(APPEND tensorslow_cxx_flags 
    -Wall -Wextra -Werror -pedantic -pedantic-errors
    -Wconversion -Wsign-conversion -Wshadow 
    -Wdouble-promotion -Wformat=2 -Wnull-dereference
    -Wold-style-cast -Woverloaded-virtual -Wunused -Wunreachable-code
    -Wdeprecated -Winvalid-pch -Wstrict-aliasing -Wstrict-overflow=5 -Wcast-align
    -Wmissing-declarations -fstack-protector-strong -D_FORTIFY_SOURCE=2)

# 可选安全选项
list(APPEND tensorslow_cxx_flags
    -fstack-protector-strong
    -D_FORTIFY_SOURCE=2
)

# 设置编译器选项以生成代码覆盖率数据
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
# 设置编译器选项以生成覆盖率数据
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} --coverage")
#set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS} --coverage")


# 生成 compile_commands.json 文件
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# 设置构建系统为 Ninja
set(CMAKE_GENERATOR Ninja)

# 设置构建命令
set(BUILD_COMMAND "ninja -j${NUM_PROCESSORS}")

# 包含源文件目录
include_directories(${tensorslow_src_dir})

# 添加源文件
set(tensorslow_frontend_files "")

enable_testing()