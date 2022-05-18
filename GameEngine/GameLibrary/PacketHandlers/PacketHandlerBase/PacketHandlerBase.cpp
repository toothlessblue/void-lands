//
// Created by ellis on 05/05/2022.
//

#include "PacketHandlerBase.h"

namespace PacketHandlers {
    void PacketHandlerBase::parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) {

    }

    unsigned char PacketHandlerBase::getCode() {
        return 0;
    }
}
