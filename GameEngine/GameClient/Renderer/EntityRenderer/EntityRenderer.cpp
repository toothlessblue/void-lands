//
// Created by ellis on 10/05/2022.
//

#include "EntityRenderer.h"
#include "../ShaderHelper/ShaderHelper.h"
#include "../../TextureLoader/TextureLoader.h"

// model coordinates
GLfloat EntityRenderer::verticalPlaneVertices[] = {
    0.5f,0.5f, 0.0f,  // top right
    0.5f,-0.5f, 0.0f,  // bottom right
    -0.5f,-0.5f, 0.0f,  // bottom left
    -0.5f,0.5f, 0.0f,   // top left
};

GLuint EntityRenderer::indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};

GLfloat EntityRenderer::uvs[] = {
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f,
};

VertexArrayBuffer* EntityRenderer::ebo;
VertexArrayBuffer* EntityRenderer::uab;
VertexArrayBuffer* EntityRenderer::vab;
VertexArrayObject* EntityRenderer::vao;

GLuint EntityRenderer::program;
GLuint EntityRenderer::textureId;

void EntityRenderer::initialise() {
    EntityRenderer::vao = new VertexArrayObject();
    EntityRenderer::vab = new VertexArrayBuffer(GL_ARRAY_BUFFER);
    EntityRenderer::uab = new VertexArrayBuffer(GL_ARRAY_BUFFER);
    EntityRenderer::ebo = new VertexArrayBuffer(GL_ELEMENT_ARRAY_BUFFER);
    EntityRenderer::textureId = TextureLoader::loadDDS("/textures/test-image.dds");

    // bind vao
    EntityRenderer::vao->bind();

    // bind vab and push data
    EntityRenderer::vab->bind();
    EntityRenderer::vab->pushBufferData(&verticalPlaneVertices[0], sizeof(EntityRenderer::verticalPlaneVertices));

    EntityRenderer::ebo->bind();
    EntityRenderer::ebo->pushBufferData(&indices[0], sizeof(indices));

    // enable and set up vertex attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    // bind and push uv data
    EntityRenderer::uab->bind();
    EntityRenderer::uab->pushBufferData(&uvs[0], sizeof(uvs));

    // uv attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    EntityRenderer::program = ShaderHelper::loadShader("SpriteUnlit");
    glUseProgram(EntityRenderer::program);
    glUniform1i(glGetUniformLocation(EntityRenderer::program, "textureSampler"), 0);

    EntityRenderer::vao->unbind();

    EntityRenderer::vab->unbind();
    EntityRenderer::ebo->unbind();
    EntityRenderer::uab->unbind();
}

bool EntityRenderer::sortingFunction(int a, int b) {
    return GameData::data.entities.zs[a] > GameData::data.entities.zs[b];
}
