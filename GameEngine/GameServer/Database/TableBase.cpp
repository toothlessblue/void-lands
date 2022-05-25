//
// Created by ellis on 18/05/22.
//

#include "TableBase.h"
#include "Database.h"
#include "TableVersions/TableVersions.h"
#include "Description/Description.h"
#include "Logger/Logger.h"
#include "DataStruct/DataStruct.h"
#include <cppconn/statement.h>
#include <string>
#include <map>
#include <set>

namespace Database {
    void TableBase::initialiseTable() {
        int databaseVersion = TableVersions::getInstance()->getVersion(this->name);

        Logger::Debug() << "Table \"" << this->name << "\" Version: " << databaseVersion;

        if (databaseVersion == -1 || !this->existsInDatabase()) {
            Logger::Info() << "Creating new table: " << this->name;
            this->createTable();
        } else if (databaseVersion < this->version) {
            Logger::Info() << "Updating table: \"" << this->name << "\", to version " << this->version;
            this->updateTable();
        } else if (databaseVersion > this->version) {
            throw std::runtime_error(std::string() + "Database has '" + this->name + "' version " + std::to_string(databaseVersion) + ", but code is version " + std::to_string(this->version));
        }
    }

    void TableBase::createTable() {
        std::string query = std::string("CREATE TABLE ") + this->name + " (";
        for (unsigned int i = 0; i < this->columns.size(); i++) {
            query += std::string() + this->columns[i].name + " " + this->columns[i].type + " " + this->columns[i].modifiers + ",";
        }
        if (this->primaryKey.size()) query += std::string() + "PRIMARY KEY (" + this->primaryKey + "),";
        query.pop_back(); // remove trailing comma
        query += ");";

        Database::execute(query);

        TableVersions::getInstance()->setVersion(this->name, this->version);
    }

    /**
     * Does NOT handle type changes, only adds or removes columns and changes primary keys
     */
    void TableBase::updateTable() {
        // get current state attributes
        std::map<std::string, DescriptionRow>* attributesWithinDb = Database::getTableColumns(this->name);
        std::map<std::string, Column> attributesWithinCode;

        for (Column column : this->columns) {
            attributesWithinCode.insert({column.name, column});
        }

        // make changes
        std::string query = std::string() + "ALTER TABLE " + this->name + " ";

        for (Column column : this->columns) {
            if (!attributesWithinDb->count(column.name)) {
                query += std::string() + "ADD " + column.name + " " + column.type + " " + column.modifiers + ",";
            }
        }

        for (std::pair<std::string, DescriptionRow> column : *attributesWithinDb) {
            if (!attributesWithinCode.count(column.second.field)) {
                query += std::string() + "DROP COLUMN " + column.second.field + ",";
            }
        }

        for (std::pair<std::string, DescriptionRow> column : *attributesWithinDb) {
            if (column.second.primary) {
                query += std::string() + "DROP PRIMARY key,";
                break;
            }
        }

        if (this->primaryKey.size()) {
            query += std::string() + "ADD PRIMARY key(" + this->primaryKey + "),";
        }

        query.pop_back();
        query += ";";

        Database::execute(query);
        Database::TableVersions::getInstance()->setVersion(this->name, this->version);

        delete attributesWithinDb;
    }

    bool TableBase::existsInDatabase() {
        if (!this->existenceChecked) {
            sql::ResultSet* result = Database::executeQueryRaw(
                std::string() + "SELECT * FROM information_schema.tables WHERE table_schema = 'db' AND table_name = '" +
                this->name + "';");

            this->exists = result->next();
            this->existenceChecked = true;

            delete result;
        }

        return this->exists;
    }

    void TableBase::dropTable() {
        Database::execute(std::string() + "DROP TABLE " + this->name + ";");
        Database::execute(std::string() + "DELETE FROM TableVersions WHERE TableName=\"" + this->name + "\";");
    }

    std::string TableBase::getColumnsAsString() {
        std::string ret;

        for (Column column : this->columns) {
            ret += std::string() + column.name + ",";
        }

        ret.pop_back();

        return ret;
    }

    void TableBase::loadIntoDataForWorld(DataStructure* data, std::string worldId) {

    }
}
