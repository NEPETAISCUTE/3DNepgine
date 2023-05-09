#ifndef VBO_HPP
#define VBO_HPP
#include <vector>
#include <glad/glad.h>

typedef unsigned int uint;

class VBO {
    uint vbo;
    std::vector<float> data;
public:
    VBO();
    VBO(const std::vector<float>& data);

    ~VBO();

    void bind();
    void unbind();
    void setData(const std::vector<float>& data);
    uint getVBO();
    const std::vector<float>& getData();

    void updateData(); //warning, binds vbo, and unbinds by definition any other vbo
};
#endif