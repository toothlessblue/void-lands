//
// Created by ellis on 05/05/2022.
//

#pragma once

#include "../PacketHandlerBase/PacketHandlerBase.h"
#include "./EntityUpdateBuilder/EntityUpdateBuilder.h"
#include <vector>
#include <functional>
#include "../PacketMetaData.h"

namespace PacketHandlers {
    class Entity : public PacketHandlerBaseCallback<std::function<void(PacketMetaData, int, int)>> {
    public:
        Entity(std::function<void(PacketMetaData, int, int)> callback);

        static EntityUpdateBuilder build(std::vector<unsigned char>* data, int id, int type);

        void parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) override;
        void onDamage(std::function<void(int, float)> callback);
        void onDestroy(std::function<void(int)> callback);
        void onHealth(std::function<void(int, float)> callback);
        void onPosition(std::function<void(int, float, float)> callback);

        unsigned char getCode() override;

    private:
        std::function<void(int, float)> _onDamage;
        std::function<void(int)> _onDestroy;
        std::function<void(int, float)> _onHealth;
        std::function<void(int, float, float)> _onPosition;
    };
}

