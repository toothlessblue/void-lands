//
// Created by ellis on 09/04/2022.
//

#pragma once
#include <vector>
#include "BytePusher/BytePusher.h"
#include "PacketHandlers/ByteIndicators.h"

class EntityUpdateBuilder {
public:
    EntityUpdateBuilder(std::vector<unsigned char>* byteVector, int id, int type);

    EntityUpdateBuilder position(float x, float z);
    EntityUpdateBuilder health(float health);
    EntityUpdateBuilder damage(float damage);
    EntityUpdateBuilder destroy();

    void end();

private:
    std::vector<unsigned char>* bytes;
};

