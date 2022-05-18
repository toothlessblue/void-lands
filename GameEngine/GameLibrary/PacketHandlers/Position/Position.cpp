//
// Created by ellis on 05/05/2022.
//

#include "Position.h"
#include "../ByteIndicators.h"
#include "BytePuller/BytePuller.h"
#include "BytePusher/BytePusher.h"

namespace PacketHandlers {
    void Position::parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) {
        float x = BytePuller::nextFloat(data, i);
        float z = BytePuller::nextFloat(data, i);

        if (this->callback != nullptr) {
            this->callback(metadata, x, z);
        }
    }

    unsigned char Position::getCode() {
        return DataIndicatorByte::Position;
    }

    void Position::build(std::vector<unsigned char>* data, float x, float z) {
        data->push_back(DataIndicatorByte::Position);
        BytePusher::pushFloat(data, x);
        BytePusher::pushFloat(data, z);
    }

    Position::Position(std::function<void(PacketMetaData, float, float)> callback) : PacketHandlerBaseCallback(callback) {

    }
}