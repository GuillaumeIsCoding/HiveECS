add_executable(ECSSandbox main.cpp)
target_include_directories(ECSSandbox PRIVATE ${CMAKE_SOURCE_DIR}/HiveECS/src)
target_link_libraries(ECSSandbox HiveECS)