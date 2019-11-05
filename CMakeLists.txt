cmake_minimum_required(VERSION 3.10)
project(MunExample VERSION 0.1.0 LANGUAGES C;CXX)

add_subdirectory(external)

add_executable(MunExample
    src/main.cc
)

target_compile_features(MunExample
    PRIVATE
        cxx_std_17
)

include(FindThreads)

target_link_libraries(MunExample
    PRIVATE
        MunRuntime
        Threads::Threads
)

add_custom_command(TARGET MunExample POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:MunRuntime>
        $<TARGET_FILE_DIR:MunExample>
)
