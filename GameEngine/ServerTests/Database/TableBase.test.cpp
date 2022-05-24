//
// Created by ellis on 24/05/22.
//

#include "../main.test.h"
#include "Database/Database.h"

class TestTable : public Database::TableBase {
private:
    static TestTable instance;

    TestTable() {
        this->name = "TestTable";
        this->version = 0;
        this->primaryKey = "id";
        this->columns = {
            {"id", "int(11)", ""},
            {"ColumnA", "int(11)", ""},
            {"ColumnB", "varchar(50)", ""},
        };
    }

public:
    static TestTable* getInstance() {
        return &TestTable::instance;
    }
};

TestTable TestTable::instance;

class TestTableV2 : public Database::TableBase {
private:
    static TestTableV2 instance;

    TestTableV2() {
        this->name = "TestTable";
        this->version = 1;
        this->primaryKey = "ColumnA";
        this->columns = {
            {"id", "int(11)", ""},
            {"ColumnA", "int(11)", ""},
            {"ColumnC", "varchar(25)", ""},
        };
    }

public:
    static TestTableV2* getInstance() {
        return &TestTableV2::instance;
    }
};

TestTableV2 TestTableV2::instance;

TEST_CASE("Add a new table") {
    Database::initialise();

    Database::addTable(TestTable::getInstance());

    REQUIRE(Database::tables.back() == TestTable::getInstance());
    REQUIRE(TestTable::getInstance()->existsInDatabase());

    std::map<std::string, Database::DescriptionRow>* columns = Database::getTableColumns(TestTable::getInstance()->name);
    REQUIRE(columns->count("id"));
    REQUIRE(columns->count("ColumnA"));
    REQUIRE(columns->count("ColumnB"));

    REQUIRE((*columns)["id"].type == "int(11)");
    REQUIRE((*columns)["ColumnA"].type == "int(11)");
    REQUIRE((*columns)["ColumnB"].type == "varchar(50)");

    REQUIRE((*columns)["id"].primary);
    REQUIRE(!(*columns)["ColumnA"].primary);
    REQUIRE(!(*columns)["ColumnB"].primary);

    delete columns;
}

TEST_CASE("Updates a table to newer version") {
    Database::initialise();

    TestTableV2::getInstance()->initialiseTable();

    REQUIRE(Database::tables.back() == TestTable::getInstance());
    REQUIRE(TestTable::getInstance()->existsInDatabase());

    std::map<std::string, Database::DescriptionRow>* columns = Database::getTableColumns(TestTable::getInstance()->name);
    REQUIRE(columns->count("id"));
    REQUIRE(columns->count("ColumnA"));
    REQUIRE(columns->count("ColumnC"));

    REQUIRE((*columns)["id"].type == "int(11)");
    REQUIRE((*columns)["ColumnA"].type == "int(11)");
    REQUIRE((*columns)["ColumnC"].type == "varchar(25)");

    REQUIRE(!(*columns)["id"].primary);
    REQUIRE((*columns)["ColumnA"].primary);
    REQUIRE(!(*columns)["ColumnC"].primary);

    TestTable::getInstance()->dropTable();
    delete columns;
}
