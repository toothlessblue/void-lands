//
// Created by ellis on 09/04/2022.
//

#include "EntityUpdateBuilder.h"

EntityUpdateBuilder::EntityUpdateBuilder(std::vector<unsigned char>* byteVector, int id, int type) {
    this->bytes = byteVector;
    this->bytes->push_back(DataIndicatorByte::BeginEntity);

    BytePusher::pushInt(this->bytes, id);
    BytePusher::pushInt(this->bytes, type);
}

EntityUpdateBuilder EntityUpdateBuilder::position(float x, float z) {
    this->bytes->push_back(EntityDataIndicatorByte::Position);
    BytePusher::pushFloat(this->bytes, x);
    BytePusher::pushFloat(this->bytes, z);
    return *this;
}

EntityUpdateBuilder EntityUpdateBuilder::health(float health) {
    this->bytes->push_back(EntityDataIndicatorByte::Health);
    BytePusher::pushFloat(this->bytes, health);
    return *this;
}

EntityUpdateBuilder EntityUpdateBuilder::damage(float damage) {
    this->bytes->push_back(EntityDataIndicatorByte::Damage);
    BytePusher::pushFloat(this->bytes, damage);
    return *this;
}

EntityUpdateBuilder EntityUpdateBuilder::destroy() {
    this->bytes->push_back(EntityDataIndicatorByte::Destroy);
    return *this;
}

void EntityUpdateBuilder::end() {
    this->bytes->push_back(DataIndicatorByte::EndEntity);
}
