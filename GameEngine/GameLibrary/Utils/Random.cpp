//
// Created by ellis on 26/05/22.
//

#include "Random.h"

namespace Random {
    std::random_device rd;
    std::mt19937 engine(rd());

    float randomFloat(float low, float high) {
        std::uniform_real_distribution<> dist(low, high);

        return dist(Random::engine);
    }
}