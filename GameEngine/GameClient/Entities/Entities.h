//
// Created by ellis on 29/03/2022.
//

#pragma once
#include <vector>
#include <unordered_map>
#include <GLES3/gl3.h>
#include "../Transform/Transform.h"
#include "../Renderer/VertexArrayObject/VertexArrayObject.h"
#include "../Renderer/VertexArrayBuffer/VertexArrayBuffer.h"
#include "../Camera/Camera.h"

struct Animation {
    unsigned int frame = 0;
    unsigned int row = 0;
    unsigned int rows = 1;
    unsigned int columns = 1;
};

class Entities {
public:
    static std::vector<unsigned int> ids;
    static std::vector<Transform> transforms;
    static std::vector<Animation> animations;
    static std::vector<GLuint> spriteTextures;
    static std::vector<float> maxHealths;
    static std::vector<float> healths;

    static void initialise();
    static unsigned int create(unsigned int serverId, GLuint textureId);
    static void deleteByIndex(unsigned int index);
    static unsigned int getIndexById(unsigned int id);
    static void renderEntities();

private:
    static unsigned int nextId;

    static bool sortingFunction(int a, int b);
    
    static VertexArrayObject* vao;
    static VertexArrayBuffer* vab;
    static VertexArrayBuffer* ebo;
    static VertexArrayBuffer* uab;

    static GLfloat verticalPlaneVertices[];
    static GLuint indices[];
    static GLfloat uvs[];

    static GLuint program;
};

