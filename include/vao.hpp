#ifndef VAO_HPP
#define VAO_HPP

#include <vbo.hpp>
#include <ebo.hpp>
#include <array>

struct attribDescriptor {
    uint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    const void* pointer;

    attribDescriptor(uint size,
                    GLenum type,
                    GLboolean normalized,
                    GLsizei stride,
                    const void* pointer);
};

class VAO {

    uint vao;
    VBO* vbo;
    EBO* ebo;

public:
    VAO(VBO* vbo, const std::vector<attribDescriptor>& attributes);
    VAO(VBO* vbo, EBO* ebo, const std::vector<attribDescriptor>& attributes);

    ~VAO();

    void init(VBO* vbo, const std::vector<attribDescriptor>& attributes);

    void bind();
    void unbind();
    void updateData();
};
#endif