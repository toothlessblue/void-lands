//
// Created by ellis on 18/05/22.
//


#pragma once
#include "../TableBase.h"

namespace Database {
    class TableVersions : public TableBase {
    private:
        static TableVersions instance;

        TableVersions() {
            this->VERSION = 1;
            this->NAME = "TableVersions";
            this->COLUMNS = new Column[2] {
                {"tableName", "VARCHAR(20)", "PRIMARY KEY"},
                {"version", "INT UNSIGNED", ""},
            };
        }
    public:
        static TableVersions* getInstance();

        unsigned int getVersion(const char* tableName);
        void setVersion(const char* tableName, unsigned int version);
    };
}
