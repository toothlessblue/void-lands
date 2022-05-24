//
// Created by ellis on 18/04/2022.
//

#pragma once
#include <string>
#include <thread>
#include <set>
#include <unordered_map>
#include "PacketHandlers/PacketMetaData.h"
#include "PacketHandlers/PacketParser/PacketParser.h"
#include "DataStruct/DataStruct.h"

class WebsocketServer;

class World {
public:
    static const unsigned int TICK_TIME_MILLISECONDS = 50;

    World(std::string worldId, WebsocketServer* server);

    void run();

    void onMessage(int connectionId, const unsigned char* payload, int length);
    void onConnect(int connectionId);
    void onDisconnect(int connectionId);

    void sendMessage(int connectionId, const unsigned char* payload, int length);


    void stop();

    int getConnectedCount();
    std::string getWorldId();
private:
    void initialiseNewConnection(int connectionId, int playerEntityId);

    void onPosition(PacketHandlers::PacketMetaData metaData, float x, float z);
    void onCraft(PacketHandlers::PacketMetaData metaData, int itemId);
    void onPlace(PacketHandlers::PacketMetaData metaData, int itemId, float x, float z);
    void onPickUp(PacketHandlers::PacketMetaData metaData, int entityId);
    void onPing(PacketHandlers::PacketMetaData metaData);
    void onDropItem(PacketHandlers::PacketMetaData metaData, int itemId);

    PacketHandlers::PacketParser messageParser;

    WebsocketServer* server;

    int connectedCount = 0;
    std::string worldId;
    std::thread runThread;
    bool running = true;

    std::set<int> connectionIds;
    std::unordered_map<int, unsigned int> connectionToEntity;
    unsigned int nextEntityId = 0;

    unsigned int createEntityId();

    DataStructure data;
};

