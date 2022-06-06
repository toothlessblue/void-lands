//
// Created by ellis on 31/05/22.
//


#pragma once


#include <GLES3/gl3.h>
#include "../ResourceFetcher/ResourceFetcher.h"
#include "../TextureLoader/TextureLoader.h"

class NetworkTexture {
public:
    NetworkTexture(const char* url);

    GLuint getTextureId();

private:
    ResourceFetcher::Resource* resource;
    GLuint textureId = 0;
    bool loaded = false;
};
