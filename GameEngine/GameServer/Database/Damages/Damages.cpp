//
// Created by ellis on 24/05/22.
//

#include "Damages.h"

namespace Database {
    Damages Damages::instance;

    Damages::Damages() {
        this->name = "Damages";
        this->version = 1;
        this->primaryKey = "id,worldId";
        this->columns = {
            {"id",      "int",        ""},
            {"worldId", "varchar(50)",""},
            {"damage",  "float",      ""}
        };
    }

    Damages* Damages::getInstance() {
        return &Damages::instance;
    }
}
