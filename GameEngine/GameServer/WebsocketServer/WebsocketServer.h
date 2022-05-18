//
// Created by ellis on 14/04/2022.
//

#pragma once
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <queue>
#include <functional>
#include "../World/World.h"
#include "PacketHandlers/PacketParser/PacketParser.h"
#include "PacketHandlers/ConnectToWorld/ConnectToWorld.h"

class World;

typedef websocketpp::server<websocketpp::config::asio> Server;
typedef Server::connection_ptr WebsocketConnection;

class WebsocketServer {
public:
    WebsocketServer();

    void run();

    void onOpen(websocketpp::connection_hdl handle);
    void onClose(websocketpp::connection_hdl handle);
    void onMessage(websocketpp::connection_hdl handle, Server::message_ptr message);

    void relayMessageFromNode(int connectionId, const unsigned char* data, int length);

    unsigned int removeConnectionId(WebsocketConnection connection);
    unsigned int createConnectionId(WebsocketConnection connection);
private:
    // handled by removeConnectionId/createConnectionId
    std::unordered_set<unsigned int> takenConnectionIds;
    std::unordered_map<WebsocketConnection, int> connectionToId;
    std::unordered_map<int, WebsocketConnection> idToConnection;

    std::vector<World*> worlds;
    std::unordered_map<std::string, World*> idToWorld;
    std::unordered_map<WebsocketConnection, World*> connectionToWorld;

    Server server;
};

