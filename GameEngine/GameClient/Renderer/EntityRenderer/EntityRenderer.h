//
// Created by ellis on 10/05/2022.
//

#pragma once


#include "../VertexArrayObject/VertexArrayObject.h"
#include "../VertexArrayBuffer/VertexArrayBuffer.h"
#include "glm/vec3.hpp"
#include "../../Camera/Camera.h"
#include "DataStruct/DataStruct.h"
#include "glm/detail/type_mat4x4.hpp"
#include "../../Transform/Transform.h"
#include "../../GameData/GameData.h"
#include "../../NetworkTexture/NetworkTexture.h"

class EntityRenderer {
public:
    static void initialise();

    static void renderEntities();

private:
    static bool sortingFunction(int a, int b);

    static VertexArrayBuffer* ebo;
    static VertexArrayBuffer* uab;
    static VertexArrayBuffer* vab;
    static VertexArrayObject* vao;

    static GLfloat verticalPlaneVertices[12];
    static GLuint indices[6];
    static GLfloat uvs[8];
    static GLuint program;

    static NetworkTexture* texture;

};

