//
// Created by ellis on 05/05/2022.
//

#include "Entity.h"
#include "BytePuller/BytePuller.h"

namespace PacketHandlers {
    void Entity::parse(const unsigned char* data, unsigned int* i, unsigned int length, PacketMetaData metadata) {
        int entityId = BytePuller::nextInt(data, i);
        int entityType = BytePuller::nextInt(data, i);

        this->callback(metadata, entityId, entityType);

        while (*i < length) {
            unsigned char byte = BytePuller::nextByte(data, i);

            switch (byte) {
                case EntityDataIndicatorByte::Damage: {
                    float damage = BytePuller::nextFloat(data, i);

                    if (this->_onDamage != nullptr) this->_onDamage(entityId, damage);
                } break;
                case EntityDataIndicatorByte::Destroy: {
                    if (this->_onDestroy != nullptr) this->_onDestroy(entityId);
                } break;
                case EntityDataIndicatorByte::Health: {
                    float health = BytePuller::nextFloat(data, i);

                    if (this->_onHealth != nullptr) this->_onHealth(entityId, health);
                } break;
                case EntityDataIndicatorByte::Position: {
                    float x = BytePuller::nextFloat(data, i);
                    float z = BytePuller::nextFloat(data, i);

                    if (this->_onPosition != nullptr) this->_onPosition(entityId, x, z);
                } break;
                case DataIndicatorByte::EndEntity: {
                    return;
                }
                default: {
                    // TODO? Error/warn with byte code?
                } break;
            }
        }
    }

    unsigned char Entity::getCode() {
        return DataIndicatorByte::BeginEntity;
    }

    void Entity::onDamage(std::function<void(int, float)> callback) {
        this->_onDamage = callback;
    }

    void Entity::onDestroy(std::function<void(int)> callback) {
        this->_onDestroy = callback;
    }

    void Entity::onHealth(std::function<void(int, float)> callback) {
        this->_onHealth = callback;
    }

    void Entity::onPosition(std::function<void(int, float, float)> callback) {
        this->_onPosition = callback;
    }

    EntityUpdateBuilder Entity::build(std::vector<unsigned char>* data, int id, int type) {
        return EntityUpdateBuilder(data, id, type);
    }

    Entity::Entity(std::function<void(PacketMetaData, int, int)> callback) : PacketHandlerBaseCallback<std::function<void(PacketMetaData, int, int)>>(callback) {

    }
}