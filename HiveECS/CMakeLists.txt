set(CMAKE_CXX_STANDARD 20)

# Dependencies
add_subdirectory(dep/entt)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h)

add_library(HiveECS ${SOURCES})
target_link_libraries(HiveECS EnTT)
target_include_directories(HiveECS PUBLIC src)

target_include_directories(HiveECS PUBLIC dep/entt/src)

# Precompiled header file
target_precompile_headers(HiveECS PUBLIC src/hvpch.h)