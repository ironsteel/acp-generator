cmake_minimum_required(VERSION 2.8)


project(acp-gen)

add_executable(acp-gen src/ACPFile.cpp src/ACPChunk.cpp src/main.cpp)

target_link_libraries(acp-gen -lOgreMain -lpthread -lfreeimage)