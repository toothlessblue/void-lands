//
// Created by ellis on 20/03/2022.
//

#pragma once
#include <emscripten/html5.h>
#include <unordered_map>

class EmscriptenInputManager {
public:
    static void initialise();

    static int keyDownCallback(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData);
    static int keyUpCallback(int eventType, const EmscriptenKeyboardEvent *keyEvent, void *userData);

    static void clearMaps();

    static bool getKeyDown(unsigned long keyCode);
    static bool getKeyUp(unsigned long keyCode);
    static bool getKey(unsigned long keyCode);
private:
    static std::unordered_map<unsigned long, bool> keysDown;
    static std::unordered_map<unsigned long, bool> keysDownThisFrame;
    static std::unordered_map<unsigned long, bool> keysUpThisFrame;
};

