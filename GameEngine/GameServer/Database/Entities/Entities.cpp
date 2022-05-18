//
// Created by ellis on 16/05/22.
//

#include "Entities.h"

constexpr const unsigned int Database::Entities::VERSION;
constexpr const char* Database::Entities::NAME;
constexpr const char* Database::Entities::COLUMNS[];

unsigned int Database::Entities::getColumnCount() {
    return (sizeof Database::Entities::COLUMNS) / (sizeof Database::Entities::COLUMNS[0]);
}

const char* const* Database::Entities::getColumns() {
    return Database::Entities::COLUMNS;
}

const char* Database::Entities::getName() {
    return Database::Entities::NAME;
}

unsigned int Database::Entities::getVersion() {
    return Database::Entities::VERSION;
}
