//
// Created by ellis on 09/04/2022.
//

#pragma once
#include <vector>
#include <string>

class BytePusher {
public:
    static void pushFloat(std::vector<unsigned char>* byteVector, float value);
    static void pushInt(std::vector<unsigned char>* byteVector, int value);
    static void pushShortInt(std::vector<unsigned char>* byteVector, short value);
    static void pushString(std::vector<unsigned char>* byteVector, std::string value);
    static void pushByte(std::vector<unsigned char>* byteVector, unsigned char value);
};

