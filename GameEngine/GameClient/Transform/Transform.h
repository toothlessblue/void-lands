//
// Created by ellis on 19/03/2022.
//

#pragma once
#include "glm/vec3.hpp"
#include "glm/gtc/quaternion.hpp"
#include <vector>

class Transform {
public:
    glm::vec3 scale = glm::vec3(1,1,1);
    std::vector<Transform*> children;

    Transform();
    ~Transform();

    virtual glm::vec3 getPosition();
    virtual glm::vec3 getWorldPosition();
    virtual void setPosition(glm::vec3 position);

    virtual void setRotation(glm::quat rotation);
    virtual glm::quat getRotation();

    virtual void addRotation(glm::vec3 rotation);

    virtual glm::mat4 getTranslationMatrix();
    virtual glm::mat4 getRotationMatrix();
    virtual glm::mat4 getScaleMatrix();
    virtual glm::mat4 getModelMatrix();

    glm::vec3 getForwards();
    glm::vec3 getLeft();
    glm::vec3 getUp();

    virtual glm::vec2 getDimensions();

    Transform* getParent();
    virtual void setParent(Transform* parent);

protected:
    Transform* parent = nullptr;
    glm::vec3 position = glm::vec3(0,0,0);
    glm::quat rotation;
};

