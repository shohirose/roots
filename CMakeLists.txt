cmake_minimum_required(VERSION 3.8.2)
project(roots CXX)

option(ROOTS_BUILD_TESTS "Build unit tests for roots" ON)

add_library(roots INTERFACE)
target_compile_features(roots
  INTERFACE
    cxx_std_11
  )
target_compile_options(roots
  INTERFACE
    $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:
      -Wall
      -Wextra
      -Wpedantic
    >
    $<$<CXX_COMPILER_ID:MSVC>:/W3>
  )
target_include_directories(roots
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
target_compile_definitions(roots
  INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:_USE_MATH_DEFINES>
  )
add_subdirectory(include)

add_library(roots::roots ALIAS roots)

if (ROOTS_BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

# Install settings for the target
install(
  TARGETS roots
  EXPORT roots-config
  INCLUDES DESTINATION include
)

# Install the config file
install(
  EXPORT roots-config
  NAMESPACE roots::
  DESTINATION lib/cmake/roots
)

# Install header files
install(
  DIRECTORY include/roots/
  DESTINATION include/roots
  FILES_MATCHING
    PATTERN "*.hpp"
    PATTERN "CMakeLists.txt" EXCLUDE
)