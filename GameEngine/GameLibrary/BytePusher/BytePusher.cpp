//
// Created by ellis on 09/04/2022.
//

#include "BytePusher.h"

void BytePusher::pushFloat(std::vector<unsigned char>* byteVector, float value) {
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&value);
    for (std::size_t i = 0; i != sizeof(float); ++i) {
        byteVector->push_back(p[i]);
    }
}

void BytePusher::pushInt(std::vector<unsigned char>* byteVector, int value) {
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&value);
    for (std::size_t i = 0; i != sizeof(int); ++i) {
        byteVector->push_back(p[i]);
    }
}

void BytePusher::pushShortInt(std::vector<unsigned char>* byteVector, short value) {
    unsigned char const* p = reinterpret_cast<unsigned char const*>(&value);
    for (std::size_t i = 0; i != sizeof(short int); ++i) {
        byteVector->push_back(p[i]);
    }
}

void BytePusher::pushString(std::vector<unsigned char>* byteVector, std::string value) {
    for(char& c : value) {
        byteVector->push_back(c);
    }
}

void BytePusher::pushByte(std::vector<unsigned char>* byteVector, unsigned char value) {
    byteVector->push_back(value);
}
