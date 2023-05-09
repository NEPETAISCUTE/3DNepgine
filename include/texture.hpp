#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <filesystem>

#include <glad/glad.h>

class Texture {
    int width;
    int height;
    int nrChannels;

    uint texID;

    bool imageValid;
public:
    Texture(std::filesystem::path path, GLint wrap_s, GLint wrap_t, GLint min_filter, GLint mag_filter);
    ~Texture();

    bool isImageValid();
    void use();
};

#endif