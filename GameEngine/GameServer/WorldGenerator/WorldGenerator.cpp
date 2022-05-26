//
// Created by ellis on 25/05/22.
//

#include "WorldGenerator.h"
#include "EntityTypes/EntityTypes.h"

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
    }},
};