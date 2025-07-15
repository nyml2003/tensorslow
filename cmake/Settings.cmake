# 设置工作目录
set(tensorslow_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(tensorslow_src_dir ${tensorslow_dir}/src)

# 设置 C++ 标准和编译器选项
set(CMAKE_CXX_STANDARD 17) # C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制使用 C++17
set(CMAKE_CXX_EXTENSIONS OFF) # 禁用编译器特定扩展


# 使用 UTF-8 编码
if(MSVC)
    list(APPEND tensorslow_cxx_flags /utf-8)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-finput-charset=UTF-8)
endif()

include(cmake/BuildSystem.cmake)
# include(Coverage.cmake)
include(cmake/Optimizations.cmake)
include(cmake/ThirdParty.cmake)
include(cmake/Warnings.cmake)