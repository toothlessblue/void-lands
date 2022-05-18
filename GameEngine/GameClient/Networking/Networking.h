//
// Created by ellis on 24/03/2022.
//

#pragma once
#include <emscripten/websocket.h>
#include <vector>
#include "PacketHandlers/PacketParser/PacketParser.h"
#include "PacketHandlers/Entity/Entity.h"

class Networking {
public:
    static const int SERVER_PORT = 27141;

    static EMSCRIPTEN_WEBSOCKET_T websocket;

    static void initialise();

    static bool ready();

    static int onOpen(int fd, const EmscriptenWebSocketOpenEvent* event, void* userData);
    static int onClose(int fd, const EmscriptenWebSocketCloseEvent* event, void* userData);
    static int onMessage(int fd, const EmscriptenWebSocketMessageEvent* event, void* userData);

    static void sendPacket(short unsigned int packetCode, short unsigned int* data, int dataLength);

    static void sendPing();
    static void sendPong();

    /// Accepts an UpdatePacketBuilder* and sends it to the Server, then deletes it
    /// \param updatePacket
    static void sendUpdate(std::vector<unsigned char>* updatePacket);
private:
    static bool _ready;

    static PacketHandlers::PacketParser packetParser;

    static void onSetPlayerEntityId(PacketHandlers::PacketMetaData metadata, int entityId);

    static void onEntity(PacketHandlers::PacketMetaData metadata, int entityId, int type);
    static void onEntityDamage(int entityId, float damage);
    static void onEntityDestroy(int entityId);
    static void onEntityHealth(int entityId, float health);
    static void onEntityPosition(int entityId, float x, float z);
};
