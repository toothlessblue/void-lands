//
// Created by ellis on 19/03/2022.
//

#include "Window.h"
#include "../../GameLibrary/Logger/Logger.h"

bool Window::initialise() {
    glewExperimental = true; // Needed for core profile
    if( !glfwInit() )
    {
        Logger::Error() << "Failed to initialize GLFW";
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 2); // 2x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow( Window::width, Window::height, "", nullptr, nullptr);
    if( window == nullptr ) {
        Logger::Error() << "Failed to open GLFW window.";
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        Logger::Error() << "Failed to initialize GLEW";
        return false;
    }

    return true;
}
