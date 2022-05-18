//
// Created by ellis on 05/05/2022.
//

#pragma once
#include "../PacketHandlerBase/PacketHandlerBase.h"
#include <vector>
#include <functional>

namespace PacketHandlers {
    class Ping : public PacketHandlerBaseCallback<std::function<void(PacketMetaData)>> {
    public:
        Ping(std::function<void(PacketMetaData)> callback);
        static void build(std::vector<unsigned char>* data);
        void parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) override;
        unsigned char getCode() override;
    };
}

