//
// Created by ellis on 24/03/2022.
//

#include "Networking.h"
#include "../../GameLibrary/Logger/Logger.h"
#include "../Config/Config.h"
#include "PacketHandlers/ConnectToWorld/ConnectToWorld.h"
#include "PacketHandlers/ConnectToClient/ConnectToClient.h"
#include "../ControlledPlayer/ControlledPlayer.h"
#include "../GameData/GameData.h"
#include <string>
#include <vector>
#include <iostream>
#include <emscripten/websocket.h>

EMSCRIPTEN_WEBSOCKET_T Networking::websocket;
bool Networking::_ready = false;
PacketHandlers::PacketParser Networking::packetParser;

void Networking::initialise() {
    std::string websocketUrl = std::string("ws://") + Config::currentHost + ":" + std::to_string(Networking::SERVER_PORT) + Config::currentUrl;

    EmscriptenWebSocketCreateAttributes ws_attrs = {
            websocketUrl.c_str(),
            NULL,
            EM_TRUE
    };

    Networking::websocket = emscripten_websocket_new(&ws_attrs);

    emscripten_websocket_set_onopen_callback(Networking::websocket, nullptr, Networking::onOpen);
    emscripten_websocket_set_onmessage_callback(Networking::websocket, nullptr, Networking::onMessage);
    emscripten_websocket_set_onclose_callback(Networking::websocket, nullptr, Networking::onClose);

    PacketHandlers::Entity* entityParser = new PacketHandlers::Entity(&Networking::onEntity);

    Networking::packetParser.addHandler(entityParser);
    Networking::packetParser.addHandler(new PacketHandlers::ConnectToClient(&Networking::onSetPlayerEntityId));

    entityParser->onDamage(Networking::onEntityDamage);
    entityParser->onDestroy(Networking::onEntityDestroy);
    entityParser->onHealth(Networking::onEntityHealth);
    entityParser->onPosition(Networking::onEntityPosition);
}

void Networking::onEntity(PacketHandlers::PacketMetaData metadata, int entityId, int type) {
    GameData::data.addEntity(entityId, type, 0, 0);
}

void Networking::onEntityDamage(int entityId, float damage) {
    Logger::Debug() << "Got entity (" << entityId << ") Damage: " << damage;

    GameData::data.setDamage(entityId, damage);
}

void Networking::onEntityDestroy(int entityId) {
    Logger::Debug() << "Got entity (" << entityId << ") Destroy: " << entityId;

    GameData::data.removeEntity(entityId);
}

void Networking::onEntityHealth(int entityId, float health) {
    Logger::Debug() << "Got entity (" << entityId << ") Health: " << health;

    GameData::data.setMaxHealth(entityId, health);
}

void Networking::onEntityPosition(int entityId, float x, float z) {
    Logger::Debug() << "Got entity (" << entityId << ") Position: " << x << ", " << z;

    if (entityId == ControlledPlayer::getControlledEntityId()) return;

    GameData::data.moveEntity(entityId, x, z);
}

void Networking::onSetPlayerEntityId(PacketHandlers::PacketMetaData metadata, int entityId) {
    Logger::Debug() << "Got my entity ID: " << entityId;
    ControlledPlayer::setControlledEntityId(entityId);
}


int Networking::onOpen(int fd, const EmscriptenWebSocketOpenEvent* event, void* userData) {
    Logger::Info() << "Opened WebsocketConnection to Server!";
    Networking::_ready = true;

    return 0;
}

int Networking::onMessage(int fd, const EmscriptenWebSocketMessageEvent* event, void* userData) {
    Networking::packetParser.parseData(event->data, event->numBytes, {});

    return 0;
}

int Networking::onClose(int fd, const EmscriptenWebSocketCloseEvent* event, void* userData) {
    return 0;
}

void Networking::sendPacket(short unsigned int packetCode, short unsigned int* data, int dataLength) {
    unsigned char bytes[dataLength + 1];
    for (int i = 1; i < dataLength + 1; i++) {
        bytes[i] = data[i];
    }

    emscripten_websocket_send_binary(Networking::websocket, &bytes[0], 1);
}

void Networking::sendPing() {
    Logger::Info() << "Sent ping";
    unsigned char bytes[1] = { DataIndicatorByte::Ping };
    emscripten_websocket_send_binary(Networking::websocket, &bytes[0], 1);
}

void Networking::sendPong() {
    unsigned char bytes[1] = { DataIndicatorByte::Pong };
    emscripten_websocket_send_binary(Networking::websocket, &bytes[0], 1);
}

void Networking::sendUpdate(std::vector<unsigned char>* updatePacket) {
    if (updatePacket->size() == 0) return;

    Logger::Debug() << "Sent packet";

    emscripten_websocket_send_binary(Networking::websocket, &(*updatePacket)[0], updatePacket->size());
}

bool Networking::ready() {
    return Networking::_ready;
}
