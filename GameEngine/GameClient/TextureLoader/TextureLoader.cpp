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
#include <string>
#include <cstring>
#include "TextureLoader.h"
#include "../../GameLibrary/Logger/Logger.h"

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

    Logger::Info() << "Loaded image";
    return textureID;
}

unsigned int TextureLoader::loadDDS(const char* data, unsigned int length) {
    Logger::Info() << "Loading image from data";

    // TODO this is broken

    std::stringstream stream(data, length);

    /* verify the type of file */
    char fileCode[4];
    stream.read(&fileCode[0], 4);

    if (strncmp(fileCode, "DDS ", 4) != 0) {
        return 0;
    }

    /* get the surface desc */
    char header[124];
    stream.read(&header[0], 124);

    int height = *(int*) &(header[8]);
    int width = *(int*) &(header[12]);
    unsigned int linearSize = *(unsigned int*) &(header[16]);
    unsigned int mipMapCount = *(unsigned int*) &(header[24]);
    unsigned int fourCC = *(unsigned int*) &(header[80]);

    char* buffer;
    unsigned int bufferSize;
    /* how big is it going to be including all mipmaps? */
    bufferSize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (char*) malloc(bufferSize * sizeof(char));
    stream.read(buffer, bufferSize);

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

    Logger::Info() << "Loaded image";
    return textureID;
}