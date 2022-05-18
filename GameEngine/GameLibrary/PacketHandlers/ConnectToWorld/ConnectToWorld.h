//
// Created by ellis on 05/05/2022.
//

#pragma once

#include "../PacketHandlerBase/PacketHandlerBase.h"
#include "../PacketMetaData.h"
#include <vector>
#include <string>
#include <functional>

namespace PacketHandlers {
    class ConnectToWorld : public PacketHandlerBaseCallback<std::function<void(PacketMetaData, std::string)>> {
    public:
        ConnectToWorld(std::function<void(PacketMetaData, std::string)> callback);
        static void build(std::vector<unsigned char>* data, std::string worldId);
        void parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) override;
        unsigned char getCode() override;
    };
}


