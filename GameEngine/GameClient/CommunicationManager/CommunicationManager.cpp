//
// Created by ellis on 31/03/2022.
//

#include "CommunicationManager.h"
#include <vector>
#include "../Networking/Networking.h"
#include "PacketHandlers/Position/Position.h"

// Period between packets in ms (rate = 1000 / period)
#define COMMUNICATION_MANAGER_DATA_PERIOD 50;

unsigned long long int CommunicationManager::timeOfLastPacket;

bool CommunicationManager::position;
float CommunicationManager::nextPositionX;
float CommunicationManager::nextPositionZ;

void CommunicationManager::initialise() {
    CommunicationManager::timeOfLastPacket = 0;
    CommunicationManager::position = false;
}

void CommunicationManager::update() {
    if (!CommunicationManager::readyForNextPacket()) return;

    std::vector<unsigned char> packet;

    if (CommunicationManager::position) {
        CommunicationManager::position = false;
        PacketHandlers::Position::build(&packet, CommunicationManager::nextPositionX, CommunicationManager::nextPositionZ);
    }

    CommunicationManager::timeOfLastPacket = Time::currentTimeMs();
    Networking::sendUpdate(&packet);
}

void CommunicationManager::updatePosition(float x, float z) {
    CommunicationManager::position = true;
    CommunicationManager::nextPositionX = x;
    CommunicationManager::nextPositionZ = z;
}

bool CommunicationManager::readyForNextPacket() {
    return Networking::ready() && Time::currentTimeMs() - CommunicationManager::timeOfLastPacket >= COMMUNICATION_MANAGER_DATA_PERIOD;
}
