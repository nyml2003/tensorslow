cmake_minimum_required(VERSION 3.10)
project(torchlight)
include(cmake/GlobalSettings.cmake)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    include(cmake/AntlrConfigContainer.cmake)
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    include(cmake/AntlrConfigWin.cmake)
endif()

include(src/source.cmake)
include(test/unittest/unittest.cmake)
include(test/extra/extra.cmake)
message(STATUS "torchlight_frontend_files: ${torchlight_frontend_files}")
message(STATUS "torchlight_backend_files: ${torchlight_backend_files}")
message(STATUS "torchlight_common_files: ${torchlight_common_files}")

add_executable(
    torchlight_frontend
    ${torchlight_frontend_files}
    ${torchlight_common_files}
)

add_executable(
    torchlight_backend
        ${torchlight_backend_files}
        ${torchlight_common_files}
)

target_link_libraries(
    torchlight_frontend
    PRIVATE
    antlr4-runtime
)

add_custom_command(
        TARGET torchlight_frontend POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/dll"  # 源目录：项目根目录下的 dll 文件夹
        "${CMAKE_BINARY_DIR}"  # 目标目录：输出目录下的对应配置文件夹
        COMMENT "Copying DLL files from project root to output directory"
)

include(cmake/tools.cmake)