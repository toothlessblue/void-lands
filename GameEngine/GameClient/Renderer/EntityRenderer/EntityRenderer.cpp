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
NetworkTexture EntityRenderer::texture("/assets/images/test-image.dds");

void EntityRenderer::initialise() {
    EntityRenderer::vao = new VertexArrayObject();
    EntityRenderer::vab = new VertexArrayBuffer(GL_ARRAY_BUFFER);
    EntityRenderer::uab = new VertexArrayBuffer(GL_ARRAY_BUFFER);
    EntityRenderer::ebo = new VertexArrayBuffer(GL_ELEMENT_ARRAY_BUFFER);

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

void EntityRenderer::renderEntities() {
    glUseProgram(EntityRenderer::program);
    glActiveTexture(GL_TEXTURE0);
    EntityRenderer::vao->bind();

    int indexes[DataStructure::MAX_ENTITIES];

    glm::vec3 cameraPosition = Camera::getPosition();

    for (int i = 0; i < DataStructure::MAX_ENTITIES; i++) {
        indexes[i] = i;
    }

    std::sort(std::begin(indexes), std::end(indexes), &EntityRenderer::sortingFunction);
    glm::mat4 viewProjectionMatrix = Camera::getProjectionMatrix() * Camera::getViewMatrix();


    for (int i = 0; i < DataStructure::MAX_ENTITIES; i++) {
        int index = indexes[i];

        if (GameData::data.entities.ids[index] == -1) continue;

        Transform transform;
        transform.setPosition(glm::vec3(GameData::data.entities.xs[index], 0, GameData::data.entities.zs[index]));

        glm::mat4 modelViewProjection = viewProjectionMatrix * transform.getModelMatrix();
        glUniformMatrix4fv(glGetUniformLocation(EntityRenderer::program, "modelViewProjection"), 1, GL_FALSE, &modelViewProjection[0][0]);
        glBindTexture(GL_TEXTURE_2D, EntityRenderer::texture.getTextureId()); // TODO get texture by type of entity
        // TODO apply sprite map uvs
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    EntityRenderer::vao->unbind();
}
