# 设置工作目录
set(torchlight_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(torchlight_src_dir ${torchlight_dir}/src)
# 设置 C++ 标准和编译器选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_MINSIZEREL "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-gdwarf-4") # to use valgrind
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -gdwarf-4 -DNDEBUG")
set(CMAKE_EXPORT_COMPILECOMMANDS on)
set(CMAKE_GENERATOR Ninja)
set(BUILD_COMMAND "ninja -j${NUM_PROCESSORS}")

# 集成 clang-tidy
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

include_directories(${torchlight_src_dir})
set(torchlight_frontend_files "")