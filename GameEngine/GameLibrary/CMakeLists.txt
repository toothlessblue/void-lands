cmake_minimum_required(VERSION 3.21)

project(GameLibrary VERSION 1.0.0 DESCRIPTION "Code that's shared between the client and the server")
include(GNUInstallDirs)

add_library(GameLibrary STATIC Logger/Logger.h Logger/Logger.cpp Utils/MathUtils.cpp Utils/MathUtils.h Utils/VectorUtils.cpp Utils/VectorUtils.h Utils/Utils.h BytePusher/BytePusher.cpp BytePusher/BytePusher.h DataStruct/DataStruct.h DataStruct/DataStruct.cpp EntityTypes/EntityTypes.h BytePuller/BytePuller.cpp BytePuller/BytePuller.h PacketHandlers/PacketHandlerBase/PacketHandlerBase.cpp PacketHandlers/PacketHandlerBase/PacketHandlerBase.h PacketHandlers/Ping/Ping.cpp PacketHandlers/Ping/Ping.h PacketHandlers/Pong/Pong.cpp PacketHandlers/Pong/Pong.h PacketHandlers/ConnectToWorld/ConnectToWorld.cpp PacketHandlers/ConnectToWorld/ConnectToWorld.h PacketHandlers/ConnectToClient/ConnectToClient.cpp PacketHandlers/ConnectToClient/ConnectToClient.h PacketHandlers/Position/Position.cpp PacketHandlers/Position/Position.h PacketHandlers/Entity/Entity.cpp PacketHandlers/Entity/Entity.h PacketHandlers/Entity/EntityUpdateBuilder/EntityUpdateBuilder.cpp PacketHandlers/Entity/EntityUpdateBuilder/EntityUpdateBuilder.h PacketHandlers/PacketParser/PacketParser.cpp PacketHandlers/PacketParser/PacketParser.h PacketHandlers/PacketMetaData.h Utils/Random.cpp Utils/Random.h PoissonGenerator/PoissonGenerator.cpp PoissonGenerator/PoissonGenerator.h)

set_target_properties(GameLibrary PROPERTIES VERSION ${PROJECT_VERSION} PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/GameLibrary.h)

target_include_directories(GameLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS GameLibrary
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})