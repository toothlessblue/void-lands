//
// Created by ellis on 30/05/22.
//


#pragma once
#include <string>
#include <emscripten/fetch.h>
#include <unordered_map>
#include "Logger/Logger.h"

class ResourceFetcher {
public:
    enum State {
        Loading,
        Loaded,
        Failed
    };

    struct Resource {
        const char* data;
        unsigned int dataLength;
        State state;
    };

    static std::unordered_map<std::string, Resource*> fileCache;

    static void onDownloadComplete(emscripten_fetch_t* fetch);

    static void onDownloadFailed(emscripten_fetch_t* fetch);

    static Resource* getResource(std::string url);

    static Resource* startFetch(std::string url);
};