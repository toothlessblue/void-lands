//
// Created by ellis on 20/03/2022.
//

#pragma once
#include "glm/fwd.hpp"

class Camera {
public:
    static glm::mat4 getProjectionMatrix();
    static glm::mat4 getViewMatrix();
    static glm::vec3 getPosition();
};

