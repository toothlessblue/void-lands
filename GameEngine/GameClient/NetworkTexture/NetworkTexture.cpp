//
// Created by ellis on 31/05/22.
//

#include "NetworkTexture.h"

NetworkTexture::NetworkTexture(const char* url, Type type) {
    this->url = url;
    this->type = type;
}

GLuint NetworkTexture::getTextureId() {
    if (!this->resource) {
        this->resource = ResourceFetcher::getResource(std::string(this->url));
    }

    if (this->resource->state == ResourceFetcher::State::Loaded && !this->loaded) {
        this->textureId = this->loadData();
        this->loaded = true;

        Logger::Debug() << "Network loaded texture ID " << this->textureId << " for url \"" << this->url << "\"";
    }

    return this->textureId;
}

unsigned int NetworkTexture::loadData() {
    switch (this->type) {
        case Type::DDS: return TextureLoader::loadDDS(this->resource->data, this->resource->dataLength);
        case Type::PNG: return TextureLoader::loadPNG(this->resource->data, this->resource->dataLength);
        default:
            Logger::Error() << "Unknown network texture type: " << this->type;
            return 0;
    }
}
