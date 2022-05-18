//
// Created by ellis on 19/03/2022.
//

#pragma once

#include <GLES2/gl2.h>

class VertexArrayObject {
public:
    VertexArrayObject();

    void unbind();

    void bind();

private:

    GLuint id;
};

