#ifndef EBO_HPP
#define EBO_HPP
#include <vector>
#include <glad/glad.h>

typedef unsigned int uint;

class EBO {
    uint ebo;
    std::vector<uint> elData;
public:
    EBO(const std::vector<uint>& elementData);
    ~EBO();

    uint getEBO();
    const std::vector<uint>& getData();
};

#endif