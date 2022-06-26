//
// Created by ellis on 30/05/22.
//

#include "ResourceFetcher.h"
#include <emscripten/fetch.h>
#include <unordered_map>

std::unordered_map<std::string, ResourceFetcher::Resource*> ResourceFetcher::fileCache;

void ResourceFetcher::onDownloadComplete(emscripten_fetch_t* fetch) {
    std::string url(fetch->url);

    Resource* resource = ResourceFetcher::fileCache[url];

    if (resource == nullptr) {
        Logger::Error() << "Failed to download \"" << url << "\", resource is nullptr";
        return;
    }

    unsigned char* data = (unsigned char*)malloc(fetch->totalBytes * sizeof(char));
    for (int i = 0; i < fetch->totalBytes; i++) {
        data[i] = fetch->data[i];
    }

    resource->data = data;
    resource->dataLength = fetch->totalBytes;
    resource->state = State::Loaded;

    emscripten_fetch_close(fetch);
    Logger::Info() << "Downloaded \"" << url << "\" successfully";
}

void ResourceFetcher::onDownloadFailed(emscripten_fetch_t* fetch) {
    Logger::Error() << "Failed to download \"" << fetch->url << "\"";

    ResourceFetcher::fileCache[fetch->url]->state = State::Failed;

    emscripten_fetch_close(fetch);
}

ResourceFetcher::Resource* ResourceFetcher::startFetch(std::string url) {
    if (ResourceFetcher::fileCache.count(url)) return ResourceFetcher::fileCache[url]; // Never perform the same fetch twice

    Logger::Info() << "Downloading \"" << url << "\"";

    ResourceFetcher::Resource* resource = new Resource {
        {}, 0, State::Loading
    };

    ResourceFetcher::fileCache.insert({url, resource});

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);

    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = ResourceFetcher::onDownloadComplete;
    attr.onerror = ResourceFetcher::onDownloadFailed;

    emscripten_fetch(&attr, &url[0]);

    return resource;
}

ResourceFetcher::Resource* ResourceFetcher::getResource(std::string url) {
    if (!ResourceFetcher::fileCache.count(url)) {
        return ResourceFetcher::startFetch(url);
    }

    return ResourceFetcher::fileCache[url];
}