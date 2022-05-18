//
// Created by ellis on 26/03/2022.
//

#include <emscripten/emscripten.h>
#include "Config.h"

const char* Config::currentUrl;
const char* Config::currentHost;

EM_JS(const char*, getLocation, (), {
    var location = window.location.pathname;
    var length = lengthBytesUTF8(location) + 1;
    var str = _malloc(length);
    stringToUTF8(location, str, length);
    return str;
});

EM_JS(const char*, getHost, (), {
    var location = window.location.host;
    var length = lengthBytesUTF8(location) + 1;
    var str = _malloc(length);
    stringToUTF8(location, str, length);
    return str;
});

void Config::initialise() {
    Config::currentUrl = getLocation();
    Config::currentHost = getHost();
}
