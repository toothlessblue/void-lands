//
// Created by ellis on 14/04/2022.
//

#include "WebsocketServer.h"
#include "Logger/Logger.h"

unsigned int WebsocketServer::createConnectionId(WebsocketConnection connection) {
    // TODO cache these objects
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned int> distribution;

    unsigned int newId;
    do {
        newId = distribution(eng);
    } while (this->takenConnectionIds.count(newId));

    this->takenConnectionIds.insert(newId);

    this->connectionToId.insert({connection, newId});
    this->idToConnection.insert({newId, connection});

    return newId;
}

unsigned int WebsocketServer::removeConnectionId(WebsocketConnection connection) {
    unsigned int id = this->connectionToId[connection];

    this->connectionToId.erase(connection);
    this->idToConnection.erase(id);

    this->takenConnectionIds.erase(id);
    return id;
}

void WebsocketServer::onOpen(websocketpp::connection_hdl handle) {
    Logger::Debug() << "Received a new websocket connection";
    WebsocketConnection connection = this->server.get_con_from_hdl(handle);
    unsigned int connectionId = this->createConnectionId(connection);

    std::string worldId = this->server.get_con_from_hdl(handle)->get_resource();

    if (worldId.size() == 0) { // TODO world ID verification/processing
        this->server.close(handle, 1008, "Do not hail the void. You do not want it to respond.");
        return;
    }

    Logger::Info() << "Connecting a new client to world " << worldId;

    if (!this->idToWorld.count(worldId)) {
        Logger::Debug() << "Spinning up world " << worldId;

        World* newWorld = new World(worldId, this);
        this->worlds.push_back(newWorld);
        this->idToWorld.insert({worldId, newWorld});
    }

    World* world = this->idToWorld[worldId];

    this->connectionToWorld.insert({connection, world});

    world->onConnect(connectionId);
}

void WebsocketServer::onMessage(websocketpp::connection_hdl handle, Server::message_ptr message) {
    const unsigned char* payload = reinterpret_cast<const unsigned char*>(message->get_raw_payload().c_str());

    Logger::Debug() << "Got message: '" << payload << "'";

    WebsocketConnection connection = this->server.get_con_from_hdl(handle);

    if (this->connectionToWorld.count(connection)) {
        World* world = this->connectionToWorld[connection];

        Logger::Debug() << "Got message to world " << world->getWorldId();

        world->onMessage(this->connectionToId[connection], payload, message->get_raw_payload().length());

    } else {
        // Connection was not connected to a world
        // TODO disconnect
    }
}

void WebsocketServer::onClose(websocketpp::connection_hdl handle) {
    WebsocketConnection connection = this->server.get_con_from_hdl(handle);
    unsigned int connectionId = this->removeConnectionId(connection);

    if (this->connectionToWorld.count(connection)) {
        World* world = this->connectionToWorld[connection];
        world->onDisconnect(connectionId);
        this->connectionToWorld.erase(connection);

        if (world->getConnectedCount() <= 0) {
            this->worlds.erase(std::remove(this->worlds.begin(), this->worlds.end(), world), this->worlds.end());
            this->idToWorld.erase(world->getWorldId());

            Logger::Info() << "Closing world: " << world->getWorldId();

            world->stop();
        }
    }
}

void WebsocketServer::run() {
    this->server.set_open_handler(websocketpp::lib::bind(&WebsocketServer::onOpen, this, websocketpp::lib::placeholders::_1));
    this->server.set_close_handler(websocketpp::lib::bind(&WebsocketServer::onClose, this, websocketpp::lib::placeholders::_1));
    this->server.set_message_handler(websocketpp::lib::bind(&WebsocketServer::onMessage, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));

    this->server.clear_access_channels(websocketpp::log::alevel::all);

    this->server.set_reuse_addr(true);
    this->server.set_listen_backlog(4096);

    this->server.init_asio();
    this->server.listen(27141);
    this->server.start_accept();

    this->server.run();
}

void WebsocketServer::relayMessageFromNode(int connectionId, const unsigned char* data, int length) {
    if (!this->idToConnection.count(connectionId)) {
        Logger::Error() << "Got invalid connection ID from node";
        return;
    }

    WebsocketConnection connection = this->idToConnection[connectionId];

    this->server.send(connection, data, length, websocketpp::frame::opcode::binary);
}

WebsocketServer::WebsocketServer() {

}
