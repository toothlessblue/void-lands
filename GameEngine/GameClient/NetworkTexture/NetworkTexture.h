//
// Created by ellis on 31/05/22.
//


#pragma once


#include <GLES3/gl3.h>
#include "../ResourceFetcher/ResourceFetcher.h"
#include "../TextureLoader/TextureLoader.h"

class NetworkTexture {
public:
    enum Type {
        DDS,
        PNG
    };

    NetworkTexture(const char* url, Type type);

    GLuint getTextureId();

private:
    unsigned int loadData();

    ResourceFetcher::Resource* resource;
    GLuint textureId = 0;
    bool loaded = false;
    const char* url;
    Type type;
};
