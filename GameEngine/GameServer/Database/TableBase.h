//
// Created by ellis on 18/05/22.
//


#pragma once
#include <vector>
#include <string>
#include "DataStruct/DataStruct.h"

namespace Database {
    struct Column {
        const char* name;
        const char* type;
        const char* modifiers;
    };

    class TableBase {
    public:
        bool existenceChecked = false;
        bool exists = false;

        unsigned int version;
        const char* name;
        std::vector<Column> columns;
        std::string primaryKey;

        bool existsInDatabase();
        void initialiseTable();
        std::string getColumnsAsString();

        void dropTable();

        virtual void loadIntoDataForWorld(DataStructure* data, std::string worldId);
    private:
        void createTable();
        void updateTable();
    };
}
