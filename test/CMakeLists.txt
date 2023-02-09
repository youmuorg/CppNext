find_package(GTest CONFIG REQUIRED)

enable_testing()

add_executable("file_io_unittest" 
  "win32/file_io_unittest.cc"
)
target_link_libraries("file_io_unittest" PRIVATE GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests("file_io_unittest")
