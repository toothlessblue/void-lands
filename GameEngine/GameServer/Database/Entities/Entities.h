//
// Created by ellis on 16/05/22.
//

#pragma once

#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "../Database.h"
#include "../TableBase.h"

namespace Database {
    class Entities : public Database::TableBase {
    public:
        constexpr static const unsigned int VERSION = 1;
        constexpr static const char* NAME = "Entities";
        constexpr static const char* COLUMNS[] = {
            "id INT PRIMARY KEY",
            "worldId VARCHAR(50) PRIMARY KEY",
            "type INT",
            "x FLOAT",
            "z FLOAT"
        };

        struct Row {
            int id;
            int type;
            float posX;
            float posZ;
        };

        unsigned int getVersion() override;
        unsigned int getColumnCount() override;
        const char* const* getColumns() override;
        const char* getName() override;
    };
}