cmake_minimum_required(VERSION 3.21)
project(ServerTests)

include_directories("../include")
link_directories("../lib")

set(CMAKE_EXE_LINKER_FLAGS "-pthread")
add_executable(ServerTests main.test.h Database/TableBase.test.cpp)

target_link_libraries(ServerTests PRIVATE GameServerLib GameLibrary mysqlcppconn)