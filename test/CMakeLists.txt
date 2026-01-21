# test/CMakeLists.txt

add_executable(run_tests tests.cpp)

target_link_libraries(run_tests gtest gtest_main)