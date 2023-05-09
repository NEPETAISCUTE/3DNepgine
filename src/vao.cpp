#include <vao.hpp>

attribDescriptor::attribDescriptor(uint size,
                GLenum type,
                GLboolean normalized,
                GLsizei stride,
                const void* pointer)
{
    this->size = size;
    this->type = type;
    this->normalized = normalized;
    this->stride = stride;
    this->pointer = pointer;
}

VAO::VAO(VBO* vbo, const std::vector<attribDescriptor>& attributes)
{
    this->init(vbo, attributes);

    for(int i = 0; i < attributes.size(); i++) glEnableVertexAttribArray(i);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    
}

VAO::VAO(VBO* vbo, EBO* ebo, const std::vector<attribDescriptor>& attributes)
{
    this->ebo = ebo;
    this->init(vbo, attributes);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->getEBO());

    std::vector<uint> indices = ebo->getData();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(uint), indices.data(), GL_STATIC_DRAW);

    for(int i = 0; i < attributes.size(); i++) glEnableVertexAttribArray(i);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

VAO::~VAO()
{
    if(vbo!=nullptr) delete vbo;
    if(ebo!=nullptr) delete ebo;
    glDeleteVertexArrays(1, &vao);
}



void VAO::init(VBO* vbo, const std::vector<attribDescriptor>& attributes) {
    this->vbo = vbo;

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo->getVBO());

    const std::vector<float>& data = vbo->getData();
    glBufferData(GL_ARRAY_BUFFER, data.size()*sizeof(float), data.data(), GL_STATIC_DRAW);

    for(uint i = 0; i < attributes.size(); i++)
    {
        glVertexAttribPointer(i, attributes[i].size, attributes[i].type, attributes[i].normalized, attributes[i].stride, attributes[i].pointer);
    }
}

void VAO::bind() {
    glBindVertexArray(vao);
}

void VAO::unbind() {
    glBindVertexArray(0);
}