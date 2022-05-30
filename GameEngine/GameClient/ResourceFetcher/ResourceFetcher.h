//
// Created by ellis on 30/05/22.
//


#pragma once
#include <string.h>
#include <emscripten/fetch.h>
#include <unordered_map>
#include "Logger/Logger.h"

namespace ResourceFetcher {
    enum State {
        Loading,
        Loaded,
        Failed
    };

    struct Resource {
        std::string* data;
        State state;
    };

    extern std::unordered_map<std::string, Resource> fileCache;

    void onDownloadComplete(emscripten_fetch_t* fetch);

    void onDownloadFailed(emscripten_fetch_t* fetch);

    void startFetch(const char* url);
};