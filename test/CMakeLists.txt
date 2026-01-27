# test/CMakeLists.txt

add_executable(run_tests
        tests.cpp
        ../Attivita.cpp
        ../Registro.cpp
)
target_link_libraries(run_tests gtest gtest_main)
target_include_directories(run_tests PRIVATE ..)