#ifndef SHADER_HPP
#define SHADER_HPP
#include <string>
#include <filesystem>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
    uint vertShader;
    uint fragShader;
    uint geomShader;
    uint shaderProg;

    void init(const std::string& vertsrc, const std::string& fragsrc, const std::string& geomsrc="");

public:
    Shader(const std::string& vertsrc, const std::string& fragsrc, const std::string& geomsrc="");
    Shader(const std::filesystem::path& vertpath, std::filesystem::path fragpath, std::filesystem::path geompath="");
    ~Shader();

    bool isShaderValid();
    void use();

    uint getProg();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
};
#endif