//
// Created by ellis on 24/05/22.
//

#include "Healths.h"

namespace Database {
    Healths Healths::instance;

    Healths::Healths() {
        this->name = "Healths";
        this->version = 1;
        this->primaryKey = "id,worldId";
        this->columns = {
            {"id",      "int",        ""},
            {"worldId", "varchar(50)",""},
            {"health",  "float",      ""}
        };
    }

    Healths* Healths::getInstance() {
        return &Healths::instance;
    }
}
