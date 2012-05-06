cmake_minimum_required(VERSION 2.8)


project(acp-generator)

add_executable(acp-generator src/ACPFile.cpp src/ACPChunk.cpp src/main.cpp)

target_link_libraries(acp-generator -lOgreMain -lpthread -lfreeimage)