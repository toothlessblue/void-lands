//
// Created by ellis on 06/05/2022.
//

#include "PacketParser.h"
#include "Logger/Logger.h"

namespace PacketHandlers {
    void PacketParser::parseData(const unsigned char* data, int length, PacketMetaData metadata) {
        Logger::Debug() << "Parsing packet";

        unsigned int i = 0;
        while (i < length) {
            unsigned char code = data[i];

            Logger::Debug() << "Code: " << +code;

            if (this->handlers.count(code)) {
                this->handlers[code]->parse(data, &i, length, metadata);
            }

            i++;
        }
    }

    void PacketParser::addHandler(PacketHandlers::PacketHandlerBase* handler) {
        this->handlers.insert({handler->getCode(), handler});
    }

    PacketParser::~PacketParser() {
        for (auto kv : handlers) {
            delete kv.second;
        }
    }
}
