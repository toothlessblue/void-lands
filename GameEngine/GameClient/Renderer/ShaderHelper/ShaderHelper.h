//
// Created by ellis on 19/03/2022.
//

#pragma once
#include <string>
#include <GLES3/gl3.h>

class ShaderHelper {
public:
    static GLuint loadShader(const std::string& shaderName);
};

