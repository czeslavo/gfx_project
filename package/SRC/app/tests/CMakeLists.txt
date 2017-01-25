file (GLOB EXAMPLE_TESTS_SOURCE_FILES "example/*.cpp")

add_executable (run_example_tests ${EXAMPLE_TESTS_SOURCE_FILES})
target_link_libraries (run_example_tests gtest gtest_main)
add_test (example_tests run_example_tests)

