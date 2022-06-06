//
// Created by ellis on 19/03/2022.
//

#include "Logger.h"



Logger::Info::~Info() {
    std::cout << "[INFO] " << s.str() << std::endl;
}

Logger::Debug::~Debug() {
    std::cout << "[DEBUG] " << s.str() << std::endl;
}

Logger::Error::~Error() {
    std::cerr << "[ERROR] " << s.str() << std::endl;
}
