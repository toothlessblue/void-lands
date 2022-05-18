//
// Created by ellis on 18/05/22.
//


#pragma once

namespace Database {
    class TableBase {
    public:
        virtual unsigned int getVersion();
        virtual unsigned int getColumnCount();
        virtual const char* const* getColumns();
        virtual const char* getName();

        void initialiseTable();
    private:
        void createTable();
        void updateTable();
    };
}
