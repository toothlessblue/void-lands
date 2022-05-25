cmake_minimum_required(VERSION 3.21)
project(GameServerLib VERSION 1.0.0 DESCRIPTION "")
include(GNUInstallDirs)

add_library(GameServerLib STATIC WebsocketServer/WebsocketServer.cpp WebsocketServer/WebsocketServer.h Database/TableBase.cpp Database/TableBase.h Database/Database.cpp Database/Database.h World/World.cpp World/World.h Database/Entities/Entities.cpp Database/Entities/Entities.h Database/TableVersions/TableVersions.cpp Database/TableVersions/TableVersions.h Database/SQLGetter.cpp Database/SQLGetter.h Database/Description/Description.cpp Database/Description/Description.h Database/Healths/Healths.cpp Database/Healths/Healths.h Database/Damages/Damages.cpp Database/Damages/Damages.h Database/Drops/Drops.cpp Database/Drops/Drops.h Database/Worlds/Worlds.cpp Database/Worlds/Worlds.h)
set_target_properties(GameServerLib PROPERTIES VERSION ${PROJECT_VERSION} PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/GameLibrary.h)
target_include_directories(GameServerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS GameServerLib
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

target_link_libraries(GameServerLib PRIVATE GameLibrary mysqlcppconn)

project(GameServer)

include_directories("../include")
link_directories("../lib")

set(CMAKE_EXE_LINKER_FLAGS "-pthread")

add_executable(GameServer main-gameServer.cpp WorldGenerator/WorldGenerator.cpp WorldGenerator/WorldGenerator.h)

target_link_libraries(GameServer PRIVATE GameLibrary GameServerLib mysqlcppconn)

