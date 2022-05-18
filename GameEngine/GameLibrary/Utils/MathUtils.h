//
// Created by ellis on 02/04/2022.
//

#pragma once


class MathUtils {
public:
    static float bytesToFloat(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3);

    /**
     * @param msb most significant byte, the one that's bit shifted
     * @param lsb least significant byte
     * @return short int, or 16 bit int
     */
    static short int bytesTo16Int(unsigned char msb, unsigned char lsb);

    static int bytesTo32Int(unsigned char b0, unsigned char b1, unsigned char b2, unsigned char b3);
};

