find_package(GTest REQUIRED)

add_executable(roots_test
    roots_test.cpp
  )
target_link_libraries(roots_test
  PUBLIC
    roots
    GTest::GTest
    GTest::Main
  )
