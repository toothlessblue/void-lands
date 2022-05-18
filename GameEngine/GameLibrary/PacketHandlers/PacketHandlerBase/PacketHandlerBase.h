//
// Created by ellis on 05/05/2022.
//

#pragma once

#include "../PacketMetaData.h"

namespace PacketHandlers {
    class PacketHandlerBase {
    public:
        virtual void parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata);
        virtual unsigned char getCode();
    };

    template<typename CallbackType>
    class PacketHandlerBaseCallback : public PacketHandlerBase {
    public:
        PacketHandlerBaseCallback(CallbackType callback) {
            this->callback = callback;
        }

        CallbackType callback;
    };
}
