//
// Created by ellis on 18/04/2022.
//

#include "World.h"
#include "../WebsocketServer/WebsocketServer.h"
#include "PacketHandlers/Entity/Entity.h"
#include "PacketHandlers/ConnectToClient/ConnectToClient.h"
#include "Logger/Logger.h"
#include "PacketHandlers/PacketParser/PacketParser.h"
#include "PacketHandlers/Position/Position.h"
#include "PacketHandlers/Ping/Ping.h"
#include "Database/Entities/Entities.h"
#include "Database/Healths/Healths.h"
#include "Database/Drops/Drops.h"
#include "Database/Damages/Damages.h"
#include "Database/Worlds/Worlds.h"
#include "WorldGenerator/WorldGenerator.h"
#include <thread>
#include <functional>
#include <chrono>

const unsigned int World::TICK_TIME_MILLISECONDS;

World::World(std::string worldId, WebsocketServer* server) {
    this->server = server;
    this->worldId = worldId;

    if (!Database::Worlds::getInstance()->isGenerated(this->worldId)) {
        WorldGenerator::generateWorld(this->worldId);
    }

    this->loadDatabase();

    this->messageParser.addHandler(new PacketHandlers::Position(std::bind(&World::onPosition, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)));
    this->messageParser.addHandler(new PacketHandlers::Ping(std::bind(&World::onPing, this, std::placeholders::_1)));
    //this->messageParser.addHandler(new PacketHandlers::Craft(std::bind(&World::onCraft, this, std::placeholders::_1));
    //this->messageParser.addHandler(new PacketHandlers::Place(std::bind(&World::onPlace, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    //this->messageParser.addHandler(new PacketHandlers::PickUp(std::bind(&World::onPickUp, this, std::placeholders::_1));
    //this->messageParser.addHandler(new PacketHandlers::DropItem(std::bind(&World::onDropItem, this, std::placeholders::_1));

    this->runThread = std::thread(std::bind(&World::run, this));
    this->runThread.detach();

    Logger::Info() << "Starting world " << worldId << "!";
}

void World::loadDatabase() {
    for (Database::TableBase* table : Database::tables) {
        table->loadIntoDataForWorld(&this->data, this->worldId);
    }

    this->nextEntityId = Database::Entities::getInstance()->getNextEntityId(this->worldId);
}

std::string World::getWorldId() {
    return this->worldId;
}

int World::getConnectedCount() {
    return this->connectedCount;
}

void World::run() {
    this->running = true;
    while (this->running) {
        // TODO do updates
        // TODO send update packet to relevant entities

        std::vector<unsigned char> data;
        for (int entityId : this->data.entitiesWithUpdates) {
            unsigned int entityIndex = this->data.idToIndex[entityId];

            EntityUpdateBuilder entity = PacketHandlers::Entity::build(&data, entityId, this->data.entities.types[entityIndex]);


            if (this->data.dyingEntities.count(entityId)) {
                entity.destroy();
            }

            if (this->data.movedEntities.count(entityId)) {
                entity.position(this->data.entities.xs[entityIndex], this->data.entities.zs[entityIndex]);
            }

            if (this->data.healedEntities.count(entityId)) {
                entity.health(this->data.healths.maxHealths[entityId]);
            }

            if (this->data.damagedEntities.count(entityId)) {
                entity.damage(this->data.healths.damages[entityId].value);
            }

            entity.end();
        }

        this->data.clearUpdateSets();

        if (data.size() > 0) {
            // TODO duplicate packet for each connected client
            // TODO insert client specific updates

            for (int connection : this->connectionIds) {
                this->sendMessage(connection, &data[0], data.size());
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(World::TICK_TIME_MILLISECONDS));
    }

    delete this;
}

void World::onMessage(int connectionId, const unsigned char* payload, int length) {
    if (!this->running) return;

    this->messageParser.parseData(payload, length, {connectionId});
}

void World::sendMessage(int connectionId, const unsigned char* payload, int length) {
    this->server->relayMessageFromNode(connectionId, payload, length);
}

void World::onConnect(int connectionId) {
    if (!this->running) return;

    this->connectedCount++;
    this->connectionIds.insert(connectionId);

    int entityId = this->createEntityId();
    this->connectionToEntity.insert({connectionId, entityId});

    this->data.addEntity(entityId, EntityTypes::Player, 0, 0);
    this->data.setMaxHealth(entityId, 100);

    this->initialiseNewConnection(connectionId, entityId);
}

void World::onDisconnect(int connectionId) {
    this->connectedCount--;
    this->connectionIds.erase(connectionId);

    this->data.removeEntity(this->connectionToEntity[connectionId]);
}

void World::stop() {
    this->running = false;
}

unsigned int World::createEntityId() {
    unsigned int id = this->nextEntityId;
    this->nextEntityId++;

    return id;
}

void World::onPosition(PacketHandlers::PacketMetaData metadata, float x, float z) {
    // TODO verification
    int entityId = this->connectionToEntity[metadata.connectionId];

    this->data.moveEntity(entityId, x, z);
}

void World::onCraft(PacketHandlers::PacketMetaData metadata, int itemId) {

}

void World::onPlace(PacketHandlers::PacketMetaData metadata, int itemId, float x, float z) {

}

void World::onPickUp(PacketHandlers::PacketMetaData metadata, int itemId) {

}

void World::onPing(PacketHandlers::PacketMetaData metadata) {

}

void World::onDropItem(PacketHandlers::PacketMetaData metadata, int itemId) {

}

void World::initialiseNewConnection(int connectionId, int playerEntityId) {
    std::vector<unsigned char> data;

    PacketHandlers::ConnectToClient::build(&data, playerEntityId);

    for (int i = 0; i < DataStructure::MAX_ENTITIES; ++i) {
        int entityId = this->data.entities.ids[i];
        if (entityId == -1) continue;

        EntityUpdateBuilder entity = PacketHandlers::Entity::build(&data, entityId, this->data.entities.types[i]);
        entity.position(this->data.entities.xs[i], this->data.entities.zs[i]);

        if (this->data.healths.maxHealths.count(entityId)) {
            entity.health(this->data.healths.maxHealths[entityId]);
        }

        if (this->data.healths.damages.count(entityId)) {
            entity.damage(this->data.healths.damages[entityId].value);
        }

        entity.end();
    }

    this->sendMessage(connectionId, &data[0], data.size());
}

