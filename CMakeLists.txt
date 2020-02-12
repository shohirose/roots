cmake_minimum_required(VERSION 3.8)
project(roots CXX)

add_library(roots INTERFACE)
target_compile_features(roots
  INTERFACE
    cxx_std_11
  )
target_compile_options(roots
  INTERFACE
    -Wall
    -Wextra
    -Wpedantic
  )
target_include_directories(roots
  INTERFACE
    include
  )
target_compile_definitions(roots
  INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:_USE_MATH_DEFINES>
  )

enable_testing()
add_subdirectory(test)