//
// Created by ellis on 18/05/22.
//


#pragma once
#include "../TableBase.h"

namespace Database {
    class TableVersions : public TableBase {
    public:
        static const unsigned int VERSION = 1;
        constexpr static const char* NAME = "TableVersions";
        constexpr static const char* COLUMNS[] = {
            "tableName VARCHAR(20) PRIMARY KEY",
            "version INT UNSIGNED"
        };

        unsigned int getVersion() override;
        unsigned int getColumnCount() override;
        const char* const* getColumns() override;
        const char* getName() override;

        static unsigned int getVersion(const char* tableName);
        static void setVersion(const char* tableName, unsigned int version);
    };
}
