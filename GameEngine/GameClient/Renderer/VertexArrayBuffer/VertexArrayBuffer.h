//
// Created by ellis on 19/03/2022.
//

#pragma once

#include <GLES3/gl3.h>
#include <vector>

class VertexArrayBuffer {
public:
    explicit VertexArrayBuffer(GLenum target);

    void unbind();

    void bind();

    void pushBufferData(GLfloat* data, GLuint size);
    void pushBufferData(GLuint* data, GLuint size);

private:

    GLuint id;
    GLenum target;

};

