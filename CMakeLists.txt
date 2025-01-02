cmake_minimum_required(VERSION 3.28)

option(HIVE_ECS_NO_TEST "Build HiveECS without test" OFF)
option(HIVE_ECS_NO_SANDBOX "Build HiveECS without a Sample" OFF)

project(HiveECS)

add_subdirectory(HiveECS)

if (NOT HIVE_ECS_NO_SANDBOX)
    add_subdirectory(Sandbox)
endif()

if (NOT HIVE_ECS_NO_TEST)
    add_subdirectory(Test)
endif()