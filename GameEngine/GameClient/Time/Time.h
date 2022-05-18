//
// Created by ellis on 19/03/2022.
//

#pragma once
#include <chrono>

namespace Time {
    extern std::chrono::steady_clock::time_point lastStart;
    extern std::chrono::steady_clock::time_point start;
    extern std::chrono::steady_clock::time_point end;
    extern float deltaTime; // Real time between each frame start
    extern float frameTime; // Time taken to compute each frame

    extern unsigned int frameCount;

    void incrementFrameCounter();

    void frameStart();
    void frameEnd();

    unsigned long long int currentTimeMs();
}