//
// Created by ellis on 20/03/2022.
//

#include "Camera.h"
#include "../Window/Window.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

// Only ever gonna have one camera, it might as well be static

glm::mat4 Camera::getProjectionMatrix() {
    return glm::perspective(
            glm::radians(50.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
            (float)Window::width / (float)Window::height,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
            1.0f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
            100.0f             // Far clipping plane. Keep as little as possible.
    );
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(
            Camera::getPosition(), // the position of your camera, in world space
            glm::vec3(0,-1,0),   // where you want to look at, in world space
            glm::vec3(0,1,0)        // probably glm::vec3(0,1,0), but (0,-1,0) would make you looking upside-down, which can be great too
    );
}

glm::vec3 Camera::getPosition() {
    return glm::vec3(0,9,-12);
}
