//
// Created by ellis on 29/03/2022.
//

#include "Entities.h"
#include "../Renderer/ShaderHelper/ShaderHelper.h"

std::vector<unsigned int> Entities::ids;
std::vector<Transform> Entities::transforms;
std::vector<Animation> Entities::animations;
std::vector<GLuint> Entities::spriteTextures;
std::vector<float> Entities::maxHealths;
std::vector<float> Entities::healths;

// model coordinates
GLfloat Entities::verticalPlaneVertices[] = {
        0.5f,0.5f, 0.0f,  // top right
        0.5f,-0.5f, 0.0f,  // bottom right
        -0.5f,-0.5f, 0.0f,  // bottom left
        -0.5f,0.5f, 0.0f,   // top left
};

GLuint Entities::indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
};

GLfloat Entities::uvs[] = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
};

GLuint Entities::program;
unsigned int Entities::nextId = 0;

VertexArrayObject* Entities::vao;
VertexArrayBuffer* Entities::vab;
VertexArrayBuffer* Entities::uab;
VertexArrayBuffer* Entities::ebo;

void Entities::initialise() {
    Entities::vao = new VertexArrayObject();
    Entities::vab = new VertexArrayBuffer(GL_ARRAY_BUFFER);
    Entities::uab = new VertexArrayBuffer(GL_ARRAY_BUFFER);
    Entities::ebo = new VertexArrayBuffer(GL_ELEMENT_ARRAY_BUFFER);

    // bind vao
    Entities::vao->bind();

    // bind vab and push data
    Entities::vab->bind();
    Entities::vab->pushBufferData(&verticalPlaneVertices[0], sizeof(Entities::verticalPlaneVertices));

    Entities::ebo->bind();
    Entities::ebo->pushBufferData(&indices[0], sizeof(indices));

    // enable and set up vertex attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    // bind and push uv data
    Entities::uab->bind();
    Entities::uab->pushBufferData(&uvs[0], sizeof(uvs));

    // uv attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

    Entities::program = ShaderHelper::loadShader("SpriteUnlit");
    glUseProgram(Entities::program);
    glUniform1i(glGetUniformLocation(Entities::program, "textureSampler"), 0);

    Entities::vao->unbind();

    Entities::vab->unbind();
    Entities::ebo->unbind();
    Entities::uab->unbind();
}

unsigned int Entities::create(unsigned int serverId, GLuint textureId) {
    Entities::ids.push_back(Entities::nextId);
    Entities::transforms.push_back(Transform());
    Entities::animations.push_back(Animation());
    Entities::spriteTextures.push_back(textureId);
    Entities::maxHealths.push_back(1);
    Entities::healths.push_back(1);

    Entities::nextId++;

    return Entities::ids.back();
}

void Entities::deleteByIndex(unsigned int index) {
    Entities::ids.erase(Entities::ids.begin() + index);
    Entities::transforms.erase(Entities::transforms.begin() + index);
    Entities::animations.erase(Entities::animations.begin() + index);
    Entities::spriteTextures.erase(Entities::spriteTextures.begin() + index);
    Entities::maxHealths.erase(Entities::maxHealths.begin() + index);
    Entities::healths.erase(Entities::healths.begin() + index);
}

bool Entities::sortingFunction(int a, int b) {
    return Entities::transforms[a].getPosition().z > Entities::transforms[b].getPosition().z;
}

void Entities::renderEntities() {
    glUseProgram(Entities::program);
    glActiveTexture(GL_TEXTURE0);
    Entities::vao->bind();

    std::vector<int> indexes;
    glm::vec3 cameraPosition = Camera::getPosition();

    int size = Entities::ids.size();

    for (int i = 0; i < Entities::ids.size(); i++) {
        indexes.push_back(i);
    }

    std::sort(indexes.begin(), indexes.end(), Entities::sortingFunction);
    glm::mat4 viewProjectionMatrix = Camera::getProjectionMatrix() * Camera::getViewMatrix();


    for (int i = 0; i < size; i++) {
        int index = indexes[i];

        glm::mat4 modelViewProjection = viewProjectionMatrix * Entities::transforms[index].getModelMatrix();
        glUniformMatrix4fv(glGetUniformLocation(Entities::program, "modelViewProjection"), 1, GL_FALSE, &modelViewProjection[0][0]);
        glBindTexture(GL_TEXTURE_2D, Entities::spriteTextures[index]);
        // TODO apply sprite map uvs
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    Entities::vao->unbind();
}

unsigned int Entities::getIndexById(unsigned int id) {
    unsigned int index = 0;
    for (unsigned int i : Entities::ids) {
        if (i == id) break;
        index++;
    }
    return index;
}
