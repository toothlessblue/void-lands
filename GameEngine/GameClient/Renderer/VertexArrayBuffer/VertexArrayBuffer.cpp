//
// Created by ellis on 19/03/2022.
//

#include "VertexArrayBuffer.h"

VertexArrayBuffer::VertexArrayBuffer(GLenum target) {
    this->target = target;
    this->id = 0;

    glGenBuffers(1, &this->id);
}

void VertexArrayBuffer::bind() {
    glBindBuffer(this->target, this->id);
}

void VertexArrayBuffer::unbind() {
    glBindBuffer(this->target, 0);
}

void VertexArrayBuffer::pushBufferData(GLfloat* data, GLuint size) {
    glBufferData(this->target, size, data, GL_STATIC_DRAW);
}

void VertexArrayBuffer::pushBufferData(GLuint* data, GLuint size) {
    glBufferData(this->target, size, data, GL_STATIC_DRAW);
}
