cmake_minimum_required(VERSION 3.21)
project(GameServer)

include_directories("../include")
link_directories("../lib")

set(CMAKE_EXE_LINKER_FLAGS "-pthread")
add_executable(GameServer main-gameServer.cpp WebsocketServer/WebsocketServer.cpp WebsocketServer/WebsocketServer.h Database/TableBase.cpp Database/TableBase.h Database/Database.cpp Database/Database.h World/World.cpp World/World.h Database/Entities/Entities.cpp Database/Entities/Entities.h Database/TableVersions/TableVersions.cpp Database/TableVersions/TableVersions.h Database/SQLGetter.cpp Database/SQLGetter.h Database/Description/Description.cpp Database/Description/Description.h)

target_link_libraries(GameServer PRIVATE GameLibrary mysqlcppconn)