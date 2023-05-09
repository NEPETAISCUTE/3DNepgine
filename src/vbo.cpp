#include <vbo.hpp>

VBO::VBO()
{
    glGenBuffers(1, &vbo);
}

VBO::VBO(const std::vector<float>& data)
{
    glGenBuffers(1, &vbo);
    this->setData(data);
}

VBO::~VBO()
{
    glDeleteBuffers(1, &vbo);
}


void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::setData(const std::vector<float>& data)
{
    this->data = data;
}

uint VBO::getVBO() { return vbo; }
const std::vector<float>& VBO::getData() { return data; }

void VBO::updateData() //only if without VAO, else update VAO instead
{
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), data.data(), GL_STATIC_DRAW);
}