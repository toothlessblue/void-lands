//
// Created by ellis on 30/05/22.
//

#include "ResourceFetcher.h"
#include <emscripten/fetch.h>
#include <unordered_map>

namespace ResourceFetcher {
    std::unordered_map<std::string, Resource> fileCache;

    void onDownloadComplete(emscripten_fetch_t* fetch) {
        Logger::Info() << "Downloading " << fetch->url << " succeeded";

        Resource* resource = &fileCache[std::string(fetch->url)];

        resource->data = (char*)malloc(fetch->totalBytes * sizeof(char));
        Logger::Debug() << "Malloc called";
        for (int i = 0; i < fetch->totalBytes; i++) {
            resource->data[i] = fetch->data[i];
        }

        resource->state = State::Loaded;
        resource->dataLength = fetch->totalBytes;

        emscripten_fetch_close(fetch);
    }

    void onDownloadFailed(emscripten_fetch_t* fetch) {
        Logger::Error() << "Downloading " << fetch->url << " failed";

        fileCache[fetch->url].state = State::Failed;

        emscripten_fetch_close(fetch);
    }

    void startFetch(std::string url) {
        if (fileCache.count(url)) return; // Never perform the same fetch twice

        emscripten_fetch_attr_t attr;
        emscripten_fetch_attr_init(&attr);

        strcpy(attr.requestMethod, "GET");
        attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
        attr.onsuccess = ResourceFetcher::onDownloadComplete;
        attr.onerror = ResourceFetcher::onDownloadFailed;
        emscripten_fetch(&attr, &url[0]);

        fileCache.insert({url, {
            nullptr, 0, State::Loading
        }});
    }

    Resource* getResource(std::string url) {
        if (!fileCache.count(url)) {
            startFetch(url);
        }
        
        return &fileCache[url];
    }
}