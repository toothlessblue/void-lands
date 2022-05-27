//
// Created by ellis on 25/05/22.
//

#include "WorldGenerator.h"
#include "EntityTypes/EntityTypes.h"
#include "Database/Healths/Healths.h"
#include "Database/Worlds/Worlds.h"

std::unordered_map<int, std::function<void(std::string worldId, int id)>> WorldGenerator::entityGenerators = {
    {
        EntityTypes::Tree, [](std::string worldId, int id) {
        glm::vec2 point = getRandomPoint(5.0f);

        Database::Entities::getInstance()->saveEntity({
            id,
            worldId,
            EntityTypes::Tree,
            point.x,
            point.y,
        });

        Database::Healths::getInstance()->saveHealth({
            id,
            worldId,
            100
        });
    }},

    {
        EntityTypes::Rock, [](std::string worldId, int id) {
        glm::vec2 point = getRandomPoint(5.0f);

        Database::Entities::getInstance()->saveEntity({
            id,
            worldId,
            EntityTypes::Rock,
            point.x,
            point.y,
        });

        Database::Healths::getInstance()->saveHealth({
            id,
            worldId,
            100
        });
    }},
};

void WorldGenerator::generateWorld(std::string worldId) {
    Logger::Info() << "Generating world: " << worldId;

    int entityId = 0;

    for (int i = 0; i < 50; i++) {
        WorldGenerator::entityGenerators[EntityTypes::Tree](worldId, entityId++);
    }

    Database::Worlds::getInstance()->saveWorld({worldId, true});

    Logger::Info() << "Finished generating world: " << worldId;
}
