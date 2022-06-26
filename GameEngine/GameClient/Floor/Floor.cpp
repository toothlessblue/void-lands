//
// Created by ellis on 21/03/2022.
//

#include "Floor.h"
#include "../Renderer/ShaderHelper/ShaderHelper.h"
#include "../Camera/Camera.h"

VertexArrayObject* Floor::vao;
VertexArrayBuffer* Floor::vab;
VertexArrayBuffer* Floor::ebo;

// model coordinates
GLfloat Floor::vertices[] = {
        5.0f, 0.0f,  5.0f,  // top right
        5.0f, 0.0f, -5.0f,  // bottom right
        -5.0f, 0.0f, -5.0f,  // bottom left
        -5.0f, 0.0f,  5.0f,   // top left
};

GLuint Floor::indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

Transform* Floor::transform;

GLuint Floor::program;

void Floor::initialise() {
    Floor::vao = new VertexArrayObject();
    Floor::vab = new VertexArrayBuffer(GL_ARRAY_BUFFER);
    Floor::ebo = new VertexArrayBuffer(GL_ELEMENT_ARRAY_BUFFER);

    Floor::transform = new Transform();
    Floor::transform->addRotation(glm::vec3(0, 0.785398f, 0)); // rotation in radians, 45 degrees
    Floor::transform->setPosition(glm::vec3(0, 0, 0));

    glm::mat4 modelViewProjection = Camera::getProjectionMatrix() * Camera::getViewMatrix() * Floor::transform->getModelMatrix();

    // bind vao
    Floor::vao->bind();

    // bind vab and push data
    Floor::vab->bind();
    Floor::vab->pushBufferData(&vertices[0], sizeof(vertices));

    Floor::ebo->bind();
    Floor::ebo->pushBufferData(&indices[0], sizeof(indices));

    // enable and set up vertex attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    Floor::program = ShaderHelper::loadShader("SimpleColour");
    glUseProgram(Floor::program);
    glUniform3f(glGetUniformLocation(Floor::program, "inColour"), 0.576f, 0.835f, 0.286f);
    glUniformMatrix4fv(glGetUniformLocation(Floor::program, "modelViewProjection"), 1, false, &modelViewProjection[0][0]);

    Floor::vao->unbind();
    Floor::vab->unbind();
    Floor::ebo->unbind();
}

void Floor::drawFloor() {
    Floor::vao->bind();
    glUseProgram(Floor::program);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    Floor::vao->unbind();
}
