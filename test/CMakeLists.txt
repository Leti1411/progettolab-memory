
add_subdirectory(./lib/googletest)

include_directories(
        ${gtest_SOURCE_DIR}/include
        ${gtest_SOURCE_DIR}

)
set(SOURCE_TEST_FILES runAllTests.cpp Registro.cpp Attivita.cpp)
add_executable(runAllTests tests.cpp)
target_link_libraries(runAllTests gtest gtest_main core)
