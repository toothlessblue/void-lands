//
// Created by ellis on 05/05/2022.
//

#pragma once

#include "../PacketHandlerBase/PacketHandlerBase.h"
#include <vector>
#include <functional>

namespace PacketHandlers {
    class Position : public PacketHandlerBaseCallback<std::function<void(PacketMetaData, float x, float z)>> {
    public:
        Position(std::function<void(PacketMetaData, float, float)> callback);

        static void build(std::vector<unsigned char>* data, float x, float z);
        void parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) override;
        unsigned char getCode() override;
    };
}

