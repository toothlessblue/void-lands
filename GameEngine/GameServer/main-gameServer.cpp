#include "WebsocketServer/WebsocketServer.h"
#include "Logger/Logger.h"
#include "Database/Database.h"

int main() {
    Logger::Info() << "Starting node";

    Database::initialise();
    WebsocketServer server;
    server.run();

    Logger::Info() << "Exiting main thread";

    return 0;
}