//
// Created by ellis on 28/04/2022.
//

#pragma once
#include <string>
#include "Utils/MathUtils.h"

class BytePuller {
public:
    static unsigned char nextByte(const unsigned char* data, unsigned int* i);
    static int nextInt(const unsigned char* data, unsigned int* i);
    static short int next16Int(const unsigned char* data, unsigned int* i);
    static float nextFloat(const unsigned char* data, unsigned int* i);
    static std::string nextString(const unsigned char* data, unsigned int* i, int stringLength);
};

