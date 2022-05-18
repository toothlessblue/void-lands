//
// Created by ellis on 02/04/2022.
//

#include <cstring>
#include "MathUtils.h"

float MathUtils::bytesToFloat(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3) {
    float output;

    unsigned char buffer[4] = {b0, b1, b2, b3};

    memcpy(&output,buffer,sizeof(output));

    return output;
}

short int MathUtils::bytesTo16Int(unsigned char msb, unsigned char lsb) {
    return msb << 8 | lsb;
}

int MathUtils::bytesTo32Int(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3) {
    int output;

    unsigned char buffer[4] = {b0, b1, b2, b3};

    memcpy(&output,buffer,sizeof(output));

    return output;
}

