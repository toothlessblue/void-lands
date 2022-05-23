#include "WebsocketServer/WebsocketServer.h"
#include "Logger/Logger.h"
#include "Database/Database.h"
#include "Database/Entities/Entities.h"

int main() {
//    Logger::Info() << "Starting node";
//
//    WebsocketServer server;
//    server.run();
//
//    Logger::Info() << "Exiting main thread";
//
    Database::initialise();

    Database::SQLGetter<Database::EntitiesRow> results = Database::Entities::getInstance()->getEntitiesForWorld("world");
    while (results.next()) {
        Logger::Debug() << "Entity ID: " << results.getRow().id;
    }

    return 0;
}