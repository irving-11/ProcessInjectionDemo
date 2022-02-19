cmake_minimum_required(VERSION 3.14)

project(PtraceDemo VERSION 0.1 LANGUAGES C CXX)

set(APP_TARGET vul-exe)


include_directories(
    "${PROJECT_SOURCE_DIR}"
)

add_executable(vul-exe 
    "${PROJECT_SOURCE_DIR}/main.c"
)

add_executable(ptrace-exe 
    "${PROJECT_SOURCE_DIR}/ptrace-hook.c"
)
