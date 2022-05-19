//
// Created by ellis on 16/05/22.
//

#include "Entities.h"

namespace Database {
    Entities Entities::instance;

    Entities* Entities::getInstance() {
        return &Entities::instance;
    }
}
