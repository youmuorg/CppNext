cmake_minimum_required(VERSION 3.25)

enable_testing()

project("CppNext" VERSION 0.1.0)

# === Global Variable ===

# === Compiler ===
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  add_compile_options("/source-charset:utf-8" "/MP")
endif ()

include_directories(".")

add_subdirectory("./win32")
add_subdirectory("./test")
