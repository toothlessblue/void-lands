//
// Created by ellis on 27/05/22.
//

#include "TextureRegistry.h"

TextureRegistry TextureRegistry::instance;

TextureRegistry::TextureRegistry() {
    this->textureMap = {
        
    };
}

GLuint TextureRegistry::getTexture(int entityType) {
    return TextureRegistry::instance.textureMap[entityType];
}
