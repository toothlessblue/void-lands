//
// Created by ellis on 26/05/22.
//


#pragma once
#include <random>

namespace Random {
    extern std::random_device rd;
    extern std::mt19937 engine;

    float randomFloat(float low, float high);
}
