//
// Created by ellis on 05/05/2022.
//

#include "Ping.h"
#include "PacketHandlers/ByteIndicators.h"

namespace PacketHandlers {
    void Ping::parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) {
        if (this->callback != nullptr) {
            this->callback(metadata);
        }
    }

    unsigned char Ping::getCode() {
        return DataIndicatorByte::Ping;
    }

    void Ping::build(std::vector<unsigned char>* data) {
        data->push_back(DataIndicatorByte::Ping);
    }

    Ping::Ping(std::function<void(PacketMetaData)> callback) : PacketHandlerBaseCallback(callback) {

    }
}