//
// Created by ellis on 20/03/2022.
//

#pragma once


#include "../Transform/Transform.h"

class ControlledPlayer {
public:
    static void initialise();

    static unsigned int entityTransformIndex;
    static void doKeyboardControl();

    static void setControlledEntityId(int entityId);
    static int getControlledEntityId();

private:
    static int controlledEntityId;
};

