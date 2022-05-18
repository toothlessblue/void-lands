//
// Created by ellis on 20/03/2022.
//

#include "ControlledPlayer.h"
#include "../EmscriptenInputManager/EmscriptenInputManager.h"
#include "../TextureLoader/TextureLoader.h"
#include "../Time/Time.h"
#include "../CommunicationManager/CommunicationManager.h"
#include "../GameData/GameData.h"

unsigned int ControlledPlayer::entityTransformIndex;
int ControlledPlayer::controlledEntityId;

void ControlledPlayer::initialise() {
    // TODO remove
}

void ControlledPlayer::doKeyboardControl() {
    glm::vec3 direction(0, 0, 0);

    if (EmscriptenInputManager::getKey(87)) { // w
        direction += glm::vec3(0, 0, 1);
    }

    if (EmscriptenInputManager::getKey(83)) { // s
        direction -= glm::vec3(0, 0, 1);
    }

    if (EmscriptenInputManager::getKey(65)) { // a
        direction += glm::vec3(1, 0, 0);
    }

    if (EmscriptenInputManager::getKey(68)) { // d
        direction -= glm::vec3(1, 0, 0);
    }

    if (glm::length(direction) == 0) return;

    int index = GameData::data.idToIndex[ControlledPlayer::controlledEntityId];

    glm::vec3 newPosition = glm::vec3(GameData::data.entities.xs[index], 0, GameData::data.entities.zs[index]) + (glm::normalize(direction) * Time::deltaTime * 4.0f);

    GameData::data.moveEntity(ControlledPlayer::controlledEntityId, newPosition.x, newPosition.z);

    CommunicationManager::updatePosition(newPosition.x, newPosition.z);
}

void ControlledPlayer::setControlledEntityId(int entityId) {
    ControlledPlayer::controlledEntityId = entityId;
}

int ControlledPlayer::getControlledEntityId() {
    return ControlledPlayer::controlledEntityId;
}
