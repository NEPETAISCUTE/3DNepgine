#include <texture.hpp>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(std::filesystem::path path, GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter)
{
    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_2D, texID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 4);
    nrChannels=4;
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        imageValid = true;
    } else {
        std::cerr << "Failed to load texture " << path << std::endl;
        imageValid = false;
    }
}

Texture::~Texture()
{
    glDeleteTextures(1, &texID);
}

bool Texture::isImageValid() { return imageValid; }
void Texture::use() { glBindTexture(GL_TEXTURE_2D, texID); }
