//
// Created by ellis on 20/03/2022.
//

#pragma once


namespace TextureLoader {
    unsigned int loadFileDDS(const char* imagePath);
    unsigned int loadDDS(const unsigned char* data, unsigned int length);
    unsigned int loadPNG(const unsigned char* data, unsigned int length);
}

