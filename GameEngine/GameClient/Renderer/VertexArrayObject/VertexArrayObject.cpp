//
// Created by ellis on 19/03/2022.
//

#include <GLES3/gl3.h>
#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject() {
    glGenVertexArrays(1, &this->id);
}

void VertexArrayObject::bind() {
    glBindVertexArray(this->id);
}

void VertexArrayObject::unbind() {
    glBindVertexArray(0);
}
