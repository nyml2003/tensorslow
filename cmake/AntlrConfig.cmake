set(tensorslow_antlr4_grammar_dir ${tensorslow_dir}/grammar)
set(tensorslow_antlr4_generated_dir ${tensorslow_dir}/generated)
set(ANTLR_SOURCE_DIR ${tensorslow_dir}/antlr-runtime)
add_subdirectory(${ANTLR_SOURCE_DIR} ${CMAKE_BINARY_DIR}/antlr4_build)
include_directories(${tensorslow_antlr4_generated_dir})
include_directories(${ANTLR_SOURCE_DIR}/src)
set(ANTLR_GENERATION_COMPLETE_FLAG ${tensorslow_antlr4_generated_dir}/.antlr4_generation_complete)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    # Windows 使用 PowerShell 执行
    add_custom_command(
            OUTPUT ${ANTLR_GENERATION_COMPLETE_FLAG}
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${tensorslow_antlr4_generated_dir}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${tensorslow_antlr4_generated_dir}
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${tensorslow_antlr4_grammar_dir} ${tensorslow_antlr4_generated_dir}
            COMMAND powershell.exe -Command "java -jar '${tensorslow_dir}/jar/antlr-4.13.2-complete.jar' -Dlanguage=Cpp -visitor -o ${tensorslow_antlr4_generated_dir} '${tensorslow_antlr4_grammar_dir}/Python3Lexer.g4' '${tensorslow_antlr4_grammar_dir}/Python3Parser.g4'"
            COMMAND ${CMAKE_COMMAND} -E touch ${ANTLR_GENERATION_COMPLETE_FLAG}
            WORKING_DIRECTORY ${tensorslow_dir}
            COMMENT "Generating ANTLR files using local JAR (only once)"
            VERBATIM
    )
else()
    # Linux/Mac 使用直接命令
    add_custom_command(
            OUTPUT ${ANTLR_GENERATION_COMPLETE_FLAG}
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${tensorslow_antlr4_generated_dir}
            COMMAND ${CMAKE_COMMAND} -E make_directory ${tensorslow_antlr4_generated_dir}
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${tensorslow_antlr4_grammar_dir} ${tensorslow_antlr4_generated_dir}
            COMMAND java -jar ${tensorslow_dir}/jar/antlr-4.13.2-complete.jar
            -Dlanguage=Cpp
            -visitor
            -o ${tensorslow_antlr4_generated_dir}
            ${tensorslow_antlr4_grammar_dir}/Python3Lexer.g4
            ${tensorslow_antlr4_grammar_dir}/Python3Parser.g4
            COMMAND ${CMAKE_COMMAND} -E touch ${ANTLR_GENERATION_COMPLETE_FLAG}
            WORKING_DIRECTORY ${tensorslow_dir}
            COMMENT "Generating ANTLR files using local JAR (only once)"
            VERBATIM
    )
endif()

add_custom_target(antlr4_generate ALL DEPENDS ${ANTLR_GENERATION_COMPLETE_FLAG})
file(GLOB_RECURSE tensorslow_antlr4_generated_files ${tensorslow_antlr4_generated_dir}/*.cpp ${tensorslow_antlr4_generated_dir}/*.h)
set(tensorslow_frontend_files ${tensorslow_frontend_files} ${tensorslow_antlr4_generated_files})