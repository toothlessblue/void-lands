//
// Created by ellis on 09/04/2022.
//

#include "DataStruct.h"

DataStructure::DataStructure() {
    for (int i = 0; i < this->MAX_ENTITIES; i++) {
        this->entities.ids[i] = -1;
    }
}

int DataStructure::getAvailableEntityIndex() {
    for (int i = 0; i < this->MAX_ENTITIES; i++) {
        if (this->entities.ids[i] == -1) {
            return i;
        }
    }

    return -1;
}

void DataStructure::removeEntity(int id) {
    int index = this->idToIndex[id];
    this->idToIndex.erase(id);

    this->entities.ids[index] = -1;

    this->healths.damages.erase(id);
    this->healths.maxHealths.erase(id);
    this->resources.drops.erase(id);

    this->entitiesWithUpdates.insert(id);
    this->dyingEntities.insert(id);
}

void DataStructure::moveEntity(int id, float x, float z) {
    int index = this->idToIndex[id];

    this->entities.xs[index] = x;
    this->entities.zs[index] = z;

    this->entitiesWithUpdates.insert(id);
    this->movedEntities.insert(id);
}

int DataStructure::addEntity(int id, int type, float x, float z) {
    if (this->idToIndex.count(id) > 0) return this->idToIndex[id];

    int index = this->getAvailableEntityIndex();
    this->idToIndex.insert({id, index});

    this->entities.ids[index] = id;
    this->entities.types[index] = type;

    this->moveEntity(id, x, z);

    return index;
}

void DataStructure::setMaxHealth(int id, float health) {
    if (!this->healths.maxHealths.count(id)) {
        this->healths.maxHealths.insert({id, 0});
    }

    this->healths.maxHealths[id] = health;

    this->entitiesWithUpdates.insert(id);
    this->healedEntities.insert(id);
}

void DataStructure::setDamage(int id, float damage) {
    if (damage <= 0) {
        this->healths.damages.erase(id);
        return;
    }

    if (!this->healths.damages.count(id)) {
        this->healths.damages.insert({id, DataStructure::Healths::Damage()});
    }

    this->healths.damages[id].value = damage;

    if (this->healths.damages[id].value > this->healths.maxHealths[id]) {
        this->dyingEntities.insert(id);
    }

    this->entitiesWithUpdates.insert(id);
    this->damagedEntities.insert(id);
}

void DataStructure::addResource(int id, int itemId, int count) {
    this->resources.drops.insert({id, DataStructure::Resources::Drop(itemId, count)});
}

void DataStructure::clearUpdateSets() {
    this->entitiesWithUpdates.clear();
    this->dyingEntities.clear();
    this->movedEntities.clear();
    this->healedEntities.clear();
    this->damagedEntities.clear();
}




