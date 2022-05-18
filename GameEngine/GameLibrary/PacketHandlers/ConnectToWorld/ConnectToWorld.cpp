//
// Created by ellis on 05/05/2022.
//

#include "ConnectToWorld.h"
#include "../ByteIndicators.h"
#include "BytePusher/BytePusher.h"
#include "BytePuller/BytePuller.h"
#include "Logger/Logger.h"
#include <functional>

namespace PacketHandlers {
    void ConnectToWorld::parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) {
        char stringLength = BytePuller::nextByte(data, i);
        std::string worldId = BytePuller::nextString(data, i, stringLength);

        if (this->callback != nullptr) {
            this->callback(metadata, worldId);
        }
    }

    unsigned char ConnectToWorld::getCode() {
        return DataIndicatorByte::ConnectToWorld;
    }

    void ConnectToWorld::build(std::vector<unsigned char>* data, std::string worldId) {
        data->push_back(DataIndicatorByte::ConnectToWorld);
        BytePusher::pushByte(data, worldId.length());
        BytePusher::pushString(data, worldId);
    }

    ConnectToWorld::ConnectToWorld(std::function<void(PacketMetaData, std::string)> callback) : PacketHandlerBaseCallback(callback) {

    }
}