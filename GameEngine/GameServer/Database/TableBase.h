//
// Created by ellis on 18/05/22.
//


#pragma once

namespace Database {
    struct Column {
        const char* name;
        const char* type;
        const char* modifiers;
    };

    class TableBase {
    public:
        unsigned int VERSION;
        const char* NAME;
        Column* COLUMNS;

        unsigned int getColumnCount();

        bool existsInDatabase();
        void initialiseTable();
    private:
        void createTable();
        void updateTable();
    };
}
