cmake_minimum_required(VERSION 3.10)
project(torchlight)
include(cmake/GlobalSettings.cmake)

include(cmake/AntlrConfig.cmake)

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
${torchlight_common_files}
${torchlight_backend_files}
)

 target_link_libraries(torchlight_frontend antlr4-runtime)

add_executable(
torchlight_mockfront
${torchlight_mock_frontend_files}
${torchlight_common_files}
)

include(cmake/tools.cmake)