set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(dep/googletest EXCLUDE_FROM_ALL)
enable_testing()
# Specify the test executable
file(GLOB_RECURSE TEST_SOURCES HiveECS/*.cpp)
add_executable(ECSmaintest MainTest.cpp ${TEST_SOURCES})
target_include_directories(ECSmaintest PRIVATE ${CMAKE_SOURCE_DIR}/HiveECS/src)
target_link_libraries(ECSmaintest PRIVATE
        gtest
        gtest_main
        gmock
        gmock_main
        HiveECS
)
add_test(NAME maintest COMMAND ECSmaintest)


add_custom_target(clean_coverage
        COMMAND ${CMAKE_COMMAND} -E remove *.gcda
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)