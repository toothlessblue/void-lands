//
// Created by ellis on 31/03/2022.
//

#pragma once


#include "../Time/Time.h"

class CommunicationManager {
public:
    static void initialise();

    static void update();

    static void updatePosition(float x, float z);

private:
    static unsigned long long int timeOfLastPacket;

    static bool position;
    static float nextPositionX;
    static float nextPositionZ;

    static bool readyForNextPacket();
};

