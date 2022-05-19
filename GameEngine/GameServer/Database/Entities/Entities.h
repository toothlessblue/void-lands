//
// Created by ellis on 16/05/22.
//

#pragma once
#include "../TableBase.h"

namespace Database {
    class Entities : public TableBase {
    private:
        static Entities instance;

        Entities() {
            this->VERSION = 1;
            this->NAME = "Entities";
            this->COLUMNS = new Column[5] {
                {"id", "INT", "PRIMARY KEY"},
                {"worldId", "VARCHAR(50)", "PRIMARY KEY"},
                {"type", "INT"},
                {"x", "FLOAT"},
                {"z", "FLOAT"},
            };
        }

    public:
        static Entities* getInstance();

        struct Row {
            int id;
            int type;
            float posX;
            float posZ;
        };
    };
}