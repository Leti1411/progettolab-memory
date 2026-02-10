
add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}
        lib/googletest/googletest/include
)
set(SOURCE_TEST_FILES runAllTests.cpp Registro.cpp Attivita.cpp)
add_executable(run_tests tests.cpp)
target_link_libraries(run_tests gtest gtest_main core)
