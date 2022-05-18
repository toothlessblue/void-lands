//
// Created by ellis on 05/05/2022.
//

#include "Pong.h"
#include "../ByteIndicators.h"

namespace PacketHandlers {
    void Pong::build(std::vector<unsigned char>* data) {
        data->push_back(DataIndicatorByte::Pong);
    }

    void Pong::parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) {
        if (this->callback != nullptr) {
            this->callback(metadata);
        }
    }

    unsigned char Pong::getCode() {
        return DataIndicatorByte::Pong;
    }

    Pong::Pong(std::function<void(PacketMetaData)> callback) : PacketHandlerBaseCallback(callback) {

    }
}