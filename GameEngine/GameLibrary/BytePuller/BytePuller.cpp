//
// Created by ellis on 28/04/2022.
//

#include "BytePuller.h"

unsigned char BytePuller::nextByte(const unsigned char* data, unsigned int* i) {
    return data[++*i];
}

int BytePuller::nextInt(const unsigned char* data, unsigned int* i) {
    int next = MathUtils::bytesTo32Int(
            data[*i + 1],
            data[*i + 2],
            data[*i + 3],
            data[*i + 4]
    );

    *i += 4;
    return next;
}

short int BytePuller::next16Int(const unsigned char* data, unsigned int* i) {
    short int next = MathUtils::bytesTo16Int(
            data[*i + 1],
            data[*i + 2]
    );

    *i += 2;
    return next;
}

float BytePuller::nextFloat(const unsigned char* data, unsigned int* i) {
    float next = MathUtils::bytesToFloat(
            data[*i + 1],
            data[*i + 2],
            data[*i + 3],
            data[*i + 4]
    );

    *i += 4;
    return next;
}

std::string BytePuller::nextString(const unsigned char* data, unsigned int* i, int stringLength) {
    std::string s;
    for (int c = 1; c <= stringLength; c++) {
        s += data[*i + c];
    }

    *i += stringLength;
    return s;
}
