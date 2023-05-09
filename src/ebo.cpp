#include <ebo.hpp>

EBO::EBO(const std::vector<uint>& elementData)
{
    glGenBuffers(1, &ebo);
    elData = elementData;
}

EBO::~EBO()
{
    glDeleteBuffers(1, &ebo);
}

uint EBO::getEBO() { return ebo; }

const std::vector<uint>& EBO::getData()
{
    return elData;
}