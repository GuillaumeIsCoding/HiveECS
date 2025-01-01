set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

if (NOT TARGET gtest)
    add_subdirectory(dep/googletest EXCLUDE_FROM_ALL)
endif()

enable_testing()
# Specify the test executable
file(GLOB_RECURSE TEST_SOURCES HiveECS/*.cpp)
add_executable(ECSmaintest MainTest.cpp ${TEST_SOURCES})
target_include_directories(ECSmaintest PRIVATE ${CMAKE_SOURCE_DIR}/HiveECS/src)

# Using a different namespace

add_library(ECS::GTest ALIAS gtest)
add_library(ECS::GTestMain ALIAS gtest_main)
add_library(ECS::GMock ALIAS gmock)
add_library(ECS::GMockMain ALIAS gmock_main)


target_link_libraries(ECSmaintest PRIVATE
        ECS::GTest
        ECS::GTestMain
        ECS::GMock
        ECS::GMockMain
        HiveECS
)
add_test(NAME maintest COMMAND ECSmaintest)


add_custom_target(clean_coverage
        COMMAND ${CMAKE_COMMAND} -E remove *.gcda
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)