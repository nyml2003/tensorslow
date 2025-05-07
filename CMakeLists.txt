cmake_minimum_required(VERSION 3.20)
project(tensorslow)
include(cmake/GlobalSettings.cmake)
include(cmake/AntlrConfig.cmake)

include(src/source.cmake)
include(test/unittest/unittest.cmake)
include(test/extra/extra.cmake)
message(STATUS "tensorslow_frontend_files: ${tensorslow_frontend_files}")
message(STATUS "tensorslow_backend_files: ${tensorslow_backend_files}")
message(STATUS "tensorslow_common_files: ${tensorslow_common_files}")

add_library(tensorslow_common STATIC ${tensorslow_common_files})
add_dependencies(tensorslow_common antlr4_generate)

add_executable(
        tensorslow_compiler
        ${tensorslow_frontend_entry_files}
        ${tensorslow_frontend_files}
)

target_link_libraries(
        tensorslow_compiler
        antlr4_static
        tensorslow_common
)
add_dependencies(tensorslow_compiler antlr4_static tensorslow_common)

add_executable(
        tensorslow_interpreter
        ${tensorslow_backend_files}
)
target_link_libraries(
        tensorslow_interpreter
        tensorslow_common
)

add_dependencies(tensorslow_interpreter tensorslow_common)

add_executable(
        tensorslow_engine
        ${tensorslow_Engine_files}
        ${tensorslow_common_files}
        ${tensorslow_frontend_files}
)

target_link_libraries(
        tensorslow_engine
        antlr4_static
)

add_dependencies(tensorslow_engine antlr4_static tensorslow_common)

include(cmake/tools.cmake)

