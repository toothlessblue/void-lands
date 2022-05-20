//
// Created by ellis on 18/05/22.
//


#pragma once
#include "../TableBase.h"

namespace Database {
    class TableVersions : public TableBase {
    private:
        static TableVersions instance;

        TableVersions();
    public:
        static TableVersions* getInstance();

        unsigned int getVersion(const char* tableName);
        void setVersion(const char* tableName, unsigned int version);
    };
}
