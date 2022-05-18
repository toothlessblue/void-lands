//
// Created by ellis on 05/05/2022.
//

#include "ConnectToClient.h"
#include "../ByteIndicators.h"
#include "BytePusher/BytePusher.h"
#include "BytePuller/BytePuller.h"
#include <functional>

namespace PacketHandlers {
    void ConnectToClient::parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) {
        int playerEntityId = BytePuller::nextInt(data, i);

        if (this->callback != nullptr) {
            this->callback(metadata, playerEntityId);
        }
    }

    unsigned char ConnectToClient::getCode() {
        return DataIndicatorByte::ConnectToClient;
    }

    void ConnectToClient::build(std::vector<unsigned char>* data, int playerEntityId) {
        data->push_back(DataIndicatorByte::ConnectToClient);
        BytePusher::pushInt(data, playerEntityId);
    }

    ConnectToClient::ConnectToClient(std::function<void(PacketMetaData, int)> callback) : PacketHandlerBaseCallback(callback) {

    }
}