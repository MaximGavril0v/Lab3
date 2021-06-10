add_subdirectory(D:/C_Projects/Lab3/googletest-master [binary_dir])
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(Tests BinaryTreeTests.cpp)
target_link_libraries(Tests gtest gtest_main)