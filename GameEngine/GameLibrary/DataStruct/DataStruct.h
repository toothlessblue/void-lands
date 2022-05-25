//
// Created by ellis on 09/04/2022.
//

#pragma once
#include <string>
#include <unordered_map>
#include <set>
#include "../EntityTypes/EntityTypes.h"

class DataStructure {
public:
    static const int MAX_ENTITIES = 1024;

    DataStructure();

    int getAvailableEntityIndex();
    std::unordered_map<int, int> idToIndex;

    int addEntity(int id, int type, float x, float z);
    void removeEntity(int id);
    void moveEntity(int id, float x, float z);

    struct Entities {
        int ids[DataStructure::MAX_ENTITIES];
        int types[DataStructure::MAX_ENTITIES];
        float xs[DataStructure::MAX_ENTITIES];
        float zs[DataStructure::MAX_ENTITIES];
    } entities;


    void setMaxHealth(int id, float health);
    void setDamage(int id, float damage);

    struct Healths {
        struct Damage {
            float value;
            //time of last hit;
        };

        std::unordered_map<int, float> maxHealths;
        std::unordered_map<int, Damage> damages;
    } healths;

    void addResource(int id, int itemId, int count);

    struct Resources {
        struct Drop {
            int itemId;
            int count;

            Drop(int itemId, int count) {
                this->itemId = itemId;
                this->count = count;
            }
        };

        std::unordered_map<int, Drop> drops;
    } resources;

    // Sets of entity IDs used to track changes frame to frame
    void clearUpdateSets();

    std::set<int> entitiesWithUpdates;
    std::set<int> dyingEntities;
    std::set<int> movedEntities;
    std::set<int> healedEntities;
    std::set<int> damagedEntities;
};

