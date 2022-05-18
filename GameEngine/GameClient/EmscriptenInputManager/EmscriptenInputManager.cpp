//
// Created by ellis on 20/03/2022.
//

#include "EmscriptenInputManager.h"

std::unordered_map<unsigned long, bool> EmscriptenInputManager::keysDown = std::unordered_map<unsigned long, bool>();
std::unordered_map<unsigned long, bool> EmscriptenInputManager::keysDownThisFrame = std::unordered_map<unsigned long, bool>();
std::unordered_map<unsigned long, bool> EmscriptenInputManager::keysUpThisFrame = std::unordered_map<unsigned long, bool>();

void EmscriptenInputManager::initialise() {
    emscripten_set_keydown_callback("#canvas", nullptr, true, EmscriptenInputManager::keyDownCallback);
    emscripten_set_keyup_callback("#canvas", nullptr, true, EmscriptenInputManager::keyUpCallback);
}

int EmscriptenInputManager::keyDownCallback(int eventType, const EmscriptenKeyboardEvent* keyEvent, void* userData) {
    if (EmscriptenInputManager::keysDown[keyEvent->keyCode]) return 0;

    EmscriptenInputManager::keysDownThisFrame[keyEvent->keyCode] = true;
    EmscriptenInputManager::keysDown[keyEvent->keyCode] = true;

    return 0;
}

int EmscriptenInputManager::keyUpCallback(int eventType, const EmscriptenKeyboardEvent* keyEvent, void* userData) {
    EmscriptenInputManager::keysUpThisFrame[keyEvent->keyCode] = true;
    EmscriptenInputManager::keysDown[keyEvent->keyCode] = false;

    return 0;
}

// Should be called at the end of each frame
void EmscriptenInputManager::clearMaps() {
    EmscriptenInputManager::keysUpThisFrame.clear();
    EmscriptenInputManager::keysDownThisFrame.clear();
}

bool EmscriptenInputManager::getKey(unsigned long keyCode) {
    return EmscriptenInputManager::keysDown[keyCode];
}

bool EmscriptenInputManager::getKeyDown(unsigned long keyCode) {
    return EmscriptenInputManager::keysDownThisFrame[keyCode];
}

bool EmscriptenInputManager::getKeyUp(unsigned long keyCode) {
    return EmscriptenInputManager::keysUpThisFrame[keyCode];
}
