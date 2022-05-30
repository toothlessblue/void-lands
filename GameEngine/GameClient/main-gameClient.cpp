#include <emscripten/emscripten.h>
#include "Window/Window.h"
#include "Renderer/VertexArrayObject/VertexArrayObject.h"
#include "Renderer/VertexArrayBuffer/VertexArrayBuffer.h"
#include "Time/Time.h"
#include "Transform/Transform.h"
#include "Camera/Camera.h"
#include "TextureLoader/TextureLoader.h"
#include "EmscriptenInputManager/EmscriptenInputManager.h"
#include "ControlledPlayer/ControlledPlayer.h"
#include "Floor/Floor.h"
#include "Config/Config.h"
#include "CommunicationManager/CommunicationManager.h"
#include "Networking/Networking.h"
#include "Logger/Logger.h"
#include "Renderer/EntityRenderer/EntityRenderer.h"
#include "ResourceFetcher/ResourceFetcher.h"

void initialisation() {
    Config::initialise();
    Floor::initialise();
    EmscriptenInputManager::initialise();
    ControlledPlayer::initialise();
    Networking::initialise();
    CommunicationManager::initialise();
    EntityRenderer::initialise();
}

void openGLSetup() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void frameStart() {
    Time::frameStart();

    glClearColor(152.0f / 256.0f, 236.0f / 256.0f, 255.0f / 256.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void update() {
    ControlledPlayer::doKeyboardControl();

    Floor::drawFloor();
    EntityRenderer::renderEntities();

    CommunicationManager::update();
}

void frameEnd() {
    EmscriptenInputManager::clearMaps(); // Must be called *after* processing user input

    Time::frameEnd();
    Time::incrementFrameCounter();
}

void mainloop() {
    frameStart();
    update();
    frameEnd();
}

int main() {
    ResourceFetcher::startFetch("http://localhost/assets/scss/default.css");

    Logger::Info() << "Hello world!";

    emscripten_set_main_loop(mainloop, 0, 0);

    if (!Window::initialise()) {
        return -1;
    }

    openGLSetup();
    initialisation();

    return 0;
}

