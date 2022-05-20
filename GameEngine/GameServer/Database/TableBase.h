//
// Created by ellis on 18/05/22.
//


#pragma once
#include <vector>
#include <string>

namespace Database {
    struct Column {
        const char* name;
        const char* type;
        const char* modifiers;
    };

    enum ChangeType {
        Add,
        Remove,
        Modify,
    };

    struct ColumnChange {
        ChangeType type;
        Column column;
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
    private:
        void createTable();
        void updateTable();
        void compareTables();
    };
}
