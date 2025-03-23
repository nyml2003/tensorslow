# AntlrConfig.cmake
# 设置语法文件目录
set(torchlight_antlr4_grammar_dir ${torchlight_dir}/grammar)

# 设置ANTLR4生成的文件目录
set(torchlight_antlr4_generated_dir ${torchlight_dir}/generated)
message(STATUS "ANTLR4 generated files directory: ${torchlight_antlr4_generated_dir}")
file(GLOB_RECURSE torchlight_antlr4_generated_files ${torchlight_antlr4_generated_dir}/src/*.cpp ${torchlight_antlr4_generated_dir}/include/*.h)
include_directories(${torchlight_antlr4_generated_dir}/include)

add_custom_target(
    antlr4_generate
    COMMAND rm -rf ${torchlight_antlr4_generated_dir}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${torchlight_antlr4_generated_dir}/include
    COMMAND ${CMAKE_COMMAND} -E make_directory ${torchlight_antlr4_generated_dir}/src
    COMMAND java -jar /usr/local/lib/antlr-4.9.2-complete.jar 
    -Dlanguage=Cpp 
    -visitor
    -o ${torchlight_antlr4_generated_dir}/src ${torchlight_antlr4_grammar_dir}/Python3Lexer.g4
    ${torchlight_antlr4_grammar_dir}/Python3Parser.g4
    COMMAND mv ${torchlight_antlr4_generated_dir}/src/*.h ${torchlight_antlr4_generated_dir}/include
    WORKING_DIRECTORY ${torchlight_dir}
    COMMENT "Generating ANTLR files"
)

# antlr4_runtime
include_directories(/usr/include/antlr4-runtime)

set(torchlight_frontend_files ${torchlight_frontend_files} ${torchlight_antlr4_generated_files})
