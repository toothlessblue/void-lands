//
// Created by ellis on 31/05/22.
//

#include "NetworkTexture.h"

NetworkTexture::NetworkTexture(const char* url) {
    this->resource = ResourceFetcher::getResource(std::string(url));
}

GLuint NetworkTexture::getTextureId() {
    if (this->resource->state == ResourceFetcher::State::Loaded && !this->loaded) {
        this->textureId = TextureLoader::loadDDS(this->resource->data, this->resource->dataLength);
        this->loaded = true;
    }

    return this->textureId;
}
