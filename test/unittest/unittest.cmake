include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1  # 指定版本
)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(${tensorslow_dir}/test/unittest/Collections/Collections.cmake)
include(${tensorslow_dir}/test/unittest/Object/Object.cmake)