//
// Created by ellis on 27/05/22.
//


#pragma once
#include <unordered_map>
#include <GLES3/gl3.h>
#include "EntityTypes/EntityTypes.h"
#include "../TextureLoader/TextureLoader.h"

class TextureRegistry {
private:
    static TextureRegistry instance;
    std::unordered_map<int, GLuint> textureMap;
    TextureRegistry();
public:
    GLuint getTexture(int entityType);
};
