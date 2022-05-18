//
// Created by ellis on 06/05/2022.
//

#pragma once
#include "../PacketHandlerBase/PacketHandlerBase.h"
#include "PacketHandlers/PacketMetaData.h"
#include <unordered_map>

namespace PacketHandlers {
    class PacketParser {
    public:
        ~PacketParser();
        void parseData(const unsigned char* data, int length, PacketMetaData metadata);
        void addHandler(PacketHandlerBase* handler);

    private:
        std::unordered_map<unsigned char, PacketHandlerBase*> handlers;
    };
}

