find_package(GTest CONFIG REQUIRED)

file(GLOB NEXT_WIN32_UNITTEST_SOURCES "./win32/*.cpp")
add_executable(win32_unittest 
  ${NEXT_WIN32_UNITTEST_SOURCES}
)
target_link_libraries(win32_unittest PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(win32_unittest PRIVATE next_win32)

include(GoogleTest)
gtest_discover_tests(win32_unittest)
