//
// Created by ellis on 25/05/22.
//


#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <random>
#include "glm/vec2.hpp"
#include "Utils/Random.h"
#include "Database/Entities/Entities.h"
#include "Logger/Logger.h"

class WorldGenerator {
public:
    static glm::vec2 getRandomPoint(float worldRadius) {
        const float angle = 0.785398f;

        float x = Random::randomFloat(-worldRadius, worldRadius);
        float z = Random::randomFloat(-worldRadius, worldRadius);

        return glm::vec2((cos(angle) * x) - (sin(angle) * z), (sin(angle) * x) + (cos(angle) * z));
    }

    static void generateWorld(std::string worldId);

    static std::unordered_map<int, std::function<void(std::string worldId, int id)>> entityGenerators;
};
