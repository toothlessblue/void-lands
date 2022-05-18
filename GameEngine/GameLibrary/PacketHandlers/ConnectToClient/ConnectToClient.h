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
    class ConnectToClient : public PacketHandlerBaseCallback<std::function<void(PacketMetaData, int)>> {
    public:
        ConnectToClient(std::function<void(PacketMetaData, int)> callback);

        static void build(std::vector<unsigned char>* data, int playerEntityId);
        void parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) override;
        unsigned char getCode() override;
    };
}


