//
// Created by ellis on 20/03/2022.
//

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

#include <cstdio>
#include <cstdlib>
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>
#include <cstring>
#include <vector>
#include "TextureLoader.h"
#include "../../GameLibrary/Logger/Logger.h"
#include "../LodePNG/lodepng.h"

unsigned int TextureLoader::loadFileDDS(const char* imagePath) {
    Logger::Info() << "Loading image: " << imagePath;

    unsigned char header[124];

    FILE* fp;

    /* try to open the file */
    fp = fopen(imagePath, "rb");
    if (fp == nullptr)
        return 0;

    /* verify the type of file */
    char fileCode[4];
    fread(fileCode, 1, 4, fp);
    if (strncmp(fileCode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp);

    int height = *(int*) &(header[8]);
    int width = *(int*) &(header[12]);
    unsigned int linearSize = *(unsigned int*) &(header[16]);
    unsigned int mipMapCount = *(unsigned int*) &(header[24]);
    unsigned int fourCC = *(unsigned int*) &(header[80]);

    unsigned char* buffer;
    unsigned int bufferSize;
    /* how big is it going to be including all mipmaps? */
    bufferSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*) malloc(bufferSize * sizeof(unsigned char));
    fread(buffer, 1, bufferSize, fp);
    /* stop the file pointer */
    fclose(fp);

    unsigned int format;

    switch (fourCC) {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            free(buffer);
            return 0;
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (int level = 0; level < mipMapCount && (width || height); ++level)
    {
        int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                               0, size, buffer + offset);

        offset += size;
        width  /= 2;
        height /= 2;
    }
    free(buffer);

    return textureID;
}

unsigned int TextureLoader::loadDDS(const unsigned char* data, unsigned int length) {
    Logger::Info() << "Loading image from data";

    int i = 0;

    unsigned char header[124];

    /* verify the type of file */
    char fileCode[4];
    for (int _i = 0; _i < 4; _i++, i++) {
        fileCode[_i] = data[i];
    }

    if (strncmp(fileCode, "DDS ", 4) != 0) {
        Logger::Error() << "Invalid file code loading DDS, got \"" << fileCode << "\"";
        return 0;
    }

    /* get the surface desc */
    for (int _i = 0; _i < 124; _i++, i++) {
        header[_i] = data[i];
    }

    int height = *(int*) &(header[8]);
    int width = *(int*) &(header[12]);
    unsigned int linearSize = *(unsigned int*) &(header[16]);
    unsigned int mipMapCount = *(unsigned int*) &(header[24]);
    unsigned int fourCC = *(unsigned int*) &(header[80]);

    unsigned char* buffer;
    unsigned int bufferSize;
    /* how big is it going to be including all mipmaps? */
    bufferSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*) malloc(bufferSize * sizeof(unsigned char));

    for (int _i = 0; _i < bufferSize; _i++, i++) {
        buffer[_i] = data[i];
    }

    unsigned int format;

    switch (fourCC) {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            Logger::Error() << "Unhandled fourCC when loading DDS";
            free(buffer);
            return 0;
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (int level = 0; level < mipMapCount && (width || height); ++level)
    {
        int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                               0, size, buffer + offset);

        offset += size;
        width  /= 2;
        height /= 2;
    }
    free(buffer);

    return textureID;
}

unsigned int TextureLoader::loadPNG(const unsigned char* data, unsigned int length) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    unsigned error = lodepng::decode(image, width, height, data, length);
    if(error != 0) {
        Logger::Error() << error << ": " << lodepng_error_text(error);
        return 0;
    }

    // Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
    size_t u2 = 1; while(u2 < width) u2 *= 2;
    size_t v2 = 1; while(v2 < height) v2 *= 2;

    // Make power of two version of the image.
    std::vector<unsigned char> image2(u2 * v2 * 4);
    for(size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            for (size_t c = 0; c < 4; c++) {
                image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
            }
        }
    }

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);

    return textureID;
}