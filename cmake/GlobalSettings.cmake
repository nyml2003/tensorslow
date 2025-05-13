# 设置工作目录
set(tensorslow_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(tensorslow_src_dir ${tensorslow_dir}/src)

# 设置 C++ 标准和编译器选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


## 针对当前 CPU 的指令集优化
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")
#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=native")
#
#
## 向量化和数学优化
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffast-math -ftree-vectorize")
#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffast-math -ftree-vectorize")
#
## 函数内联和调试信息移除
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -finline-functions -finline-limit=10000 -g0")
#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -finline-functions -finline-limit=10000 -g0")
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
endif()
# 把warning当作error
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wsign-conversion -Wshadow")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion -Wformat=2 -Wnull-dereference")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Woverloaded-virtual")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused -Wunreachable-code")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdeprecated -Winvalid-pch -Wstrict-aliasing")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-overflow=5 -Wcast-align")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-declarations")
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