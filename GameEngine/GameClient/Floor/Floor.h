//
// Created by ellis on 21/03/2022.
//

#pragma once


#include "../Renderer/VertexArrayObject/VertexArrayObject.h"
#include "../Renderer/VertexArrayBuffer/VertexArrayBuffer.h"
#include "../Transform/Transform.h"

class Floor {
public:
    static GLfloat vertices[];
    static GLuint indices[];

    static VertexArrayObject* vao;
    static VertexArrayBuffer* vab;
    static VertexArrayBuffer* ebo;

    static GLuint program;

    static Transform* transform;

    static void initialise();
    static void drawFloor();
};

