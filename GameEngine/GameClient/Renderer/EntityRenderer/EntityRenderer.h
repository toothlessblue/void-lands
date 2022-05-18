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

class EntityRenderer {
public:
    static void initialise();

    static void renderEntities() {
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
            glBindTexture(GL_TEXTURE_2D, EntityRenderer::textureId); // TODO get texture by type of entity
            // TODO apply sprite map uvs
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        }

        EntityRenderer::vao->unbind();
    }

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

    static GLuint textureId;

};

