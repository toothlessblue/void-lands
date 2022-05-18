//
// Created by ellis on 19/03/2022.
//

#include "Transform.h"
#include "glm/gtx/quaternion.hpp"
#include "glm/vec3.hpp"
#include "glm/matrix.hpp"
#include "glm/gtc/quaternion.hpp"
#include "../../GameLibrary/Utils/VectorUtils.h"

Transform::Transform() {
    this->scale = glm::vec3(1,1,1);
    this->position = glm::vec3(0,0,0);
    this->rotation = glm::quat(glm::vec3(0,0,0));
}

Transform::~Transform() {
    for (Transform* transform : this->children) {
        transform->setParent(nullptr);
    }
}

void Transform::setRotation(glm::quat rotation) {
    this->rotation = rotation;
}

glm::quat Transform::getRotation() {
    return this->rotation;
}

void Transform::addRotation(glm::vec3 rotation) {
    this->rotation = glm::quat(rotation) * this->rotation;
}


glm::vec3 Transform::getPosition() {
    return this->position;
}

void Transform::setPosition(glm::vec3 position) {
    this->position = position;
}

glm::vec3 Transform::getWorldPosition() {
    glm::vec3 position = this->getPosition();
    while (parent) {
        position += parent->getPosition();
        parent = parent->parent;
    }
    return position;
}


glm::mat4 Transform::getTranslationMatrix() {
    return glm::translate(glm::mat4(1.0f), this->position);
}

glm::mat4 Transform::getScaleMatrix() {
    return glm::scale(glm::mat4(1.0f), this->scale);
}

glm::mat4 Transform::getRotationMatrix() {
    return glm::toMat4(this->rotation);
}

glm::mat4 Transform::getModelMatrix() {
    glm::mat4 model = this->getTranslationMatrix() * this->getRotationMatrix() * this->getScaleMatrix();

    Transform* parent = this->parent;
    while (parent) {
        model *= (parent->getTranslationMatrix() * parent->getRotationMatrix() * parent->getScaleMatrix());
        parent = parent->parent;
    }

    return model;
}


glm::vec3 Transform::getForwards() {
    return glm::rotate(glm::inverse(this->rotation), glm::vec3(0, 0, 1));
}

glm::vec3 Transform::getLeft() {
    return glm::rotate(glm::inverse(this->rotation), glm::vec3(1, 0, 0));
}

glm::vec3 Transform::getUp() {
    return glm::rotate(glm::inverse(this->rotation), glm::vec3(0, 1, 0));
}


glm::vec2 Transform::getDimensions() {
    return glm::vec2(0, 0);
}


void Transform::setParent(Transform* parent) {
    if (this->parent) {
        Utils::Vector::remove(parent->children, this);
    }

    this->parent = parent;

    if (this->parent) {
        this->parent->children.push_back(this);
    }
}

Transform* Transform::getParent() {
    return this->parent;
}