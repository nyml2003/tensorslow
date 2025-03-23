# 设置 VCPKG_ROOT 环境变量
set(VCPKG_ROOT $ENV{VCPKG_ROOT})
message(STATUS "VCPKG_ROOT: ${VCPKG_ROOT}")

# 强制指定 vcpkg 工具链文件
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# 手动指定 antlr4-runtime 的配置文件路径（根据实际路径调整）
set(antlr4-runtime_DIR "${VCPKG_ROOT}/installed/x64-mingw-dynamic/share/antlr4-runtime" CACHE PATH "")
link_directories("${VCPKG_ROOT}/installed/x64-mingw-dynamic/bin")

# 查找 antlr4-runtime 包
find_package(antlr4-runtime CONFIG REQUIRED)

# 设置源文件和生成目录
set(torchlight_antlr4_grammar_dir ${torchlight_dir}/grammar)
set(torchlight_antlr4_generated_dir ${torchlight_dir}/generated)

# 添加包含目录
include_directories(
    "${VCPKG_ROOT}/installed/x64-mingw-dynamic/include/antlr4-runtime"
    ${torchlight_antlr4_generated_dir} # 自动生成的 ANTLR 文件目录
)


message(STATUS "ANTLR4 generated files directory: ${torchlight_antlr4_generated_dir}")
file(GLOB_RECURSE torchlight_antlr4_generated_files ${torchlight_antlr4_generated_dir}/*.cpp ${torchlight_antlr4_generated_dir}/*.h)
set(torchlight_frontend_files ${torchlight_frontend_files} ${torchlight_antlr4_generated_files})

# ANTLR 生成目标
add_custom_target(
    antlr4_generate

    # 删除目录
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${torchlight_antlr4_generated_dir}

    # 创建目录
    COMMAND ${CMAKE_COMMAND} -E make_directory ${torchlight_antlr4_generated_dir}

    # 执行 ANTLR 生成
    COMMAND java -jar "${CMAKE_CURRENT_SOURCE_DIR}/jar/antlr-4.13.2-complete.jar"
    -Dlanguage=Cpp -visitor
    -o "${torchlight_antlr4_generated_dir}"
    "${torchlight_antlr4_grammar_dir}/Python3Lexer.g4"
    "${torchlight_antlr4_grammar_dir}/Python3Parser.g4"
    WORKING_DIRECTORY ${torchlight_dir}
    COMMENT "Generating ANTLR files"
)