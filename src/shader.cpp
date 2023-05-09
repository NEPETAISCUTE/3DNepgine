#include <shader.hpp>
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& vertsrc, const std::string& fragsrc, const std::string& geomsrc)
{
    this->init(vertsrc, fragsrc, geomsrc);
}

Shader::Shader(const std::filesystem::path& vertpath, std::filesystem::path fragpath, std::filesystem::path geompath)
{
    std::ifstream vertfile;
    std::string vertraw;
    vertfile.open(vertpath);
    if(vertfile.is_open())
    {
        std::string line;
        while(getline(vertfile, line)) vertraw += line + '\n';
    }
    vertfile.close();

    std::ifstream fragfile;
    std::string fragraw;
    fragfile.open(fragpath);
    if(fragfile.is_open())
    {
        std::string line;
        while(getline(fragfile, line)) fragraw += line + '\n';
    }
    fragfile.close();

    std::string geomraw = "";
    if(geompath!="")
    {
        std::ifstream geomfile;
        geomfile.open(geompath);
        if(geomfile.is_open())
        {
            std::string line;
            while(getline(geomfile, line)) geomraw += line + '\n';
        }
    }

    this->init(vertraw, fragraw, geomraw);

}

void Shader::init(const std::string& vertsrc, const std::string& fragsrc, const std::string& geomsrc)
{
    vertShader = glCreateShader(GL_VERTEX_SHADER);
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    geomShader = 0;
    shaderProg = 0;
    if(geomsrc!="") geomShader = glCreateShader(GL_GEOMETRY_SHADER);

    const char* tmpvertsrc = vertsrc.c_str();
    glShaderSource(vertShader, 1, &tmpvertsrc, nullptr);

    const char* tmpfragsrc = fragsrc.c_str();
    glShaderSource(fragShader, 1, &tmpfragsrc, nullptr);

    glCompileShader(vertShader);
    int vertsuccess;

    char infoLog[512];
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &vertsuccess);

    if(!vertsuccess)
    {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glCompileShader(fragShader);
    int fragsuccess;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &fragsuccess);

    if(!fragsuccess)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    if(vertsuccess && fragsuccess) {
        shaderProg = glCreateProgram();
        glAttachShader(shaderProg, vertShader);
        glAttachShader(shaderProg, fragShader);
    }
    if(geomShader!=0)
    {
        const char* tmpgeomsrc = geomsrc.c_str();
        glShaderSource(geomShader, 1, &tmpgeomsrc, nullptr);
        glCompileShader(geomShader);
        int geomsuccess;

        glGetShaderiv(geomShader, GL_COMPILE_STATUS, &geomsuccess);

        if(vertsuccess && fragsuccess && geomsuccess){
            glAttachShader(shaderProg, geomShader);
        } else {
            glGetShaderInfoLog(geomShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            return;
        }
    }

    if(vertsuccess && fragsuccess) {
        int success;
        glLinkProgram(shaderProg);
        glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shaderProg, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    if(geomShader!=0) glDeleteShader(geomShader);
}

Shader::~Shader()
{
    glDeleteProgram(shaderProg);
}

bool Shader::isShaderValid()
{
    return shaderProg!=0;
}

void Shader::use()
{
    glUseProgram(shaderProg);
}

uint Shader::getProg() { return shaderProg; }

void Shader::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(shaderProg, name.c_str()), (int) value);
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(shaderProg, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(shaderProg, name.c_str()), value);
}
void Shader::setVec3(const std::string &name, glm::vec3 value) const {
    glUniform3fv(glGetUniformLocation(shaderProg, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setVec3(const std::string &name, float x, float y, float z) const {
    glm::vec3 v(x, y, z);
    glUniform3fv(glGetUniformLocation(shaderProg, name.c_str()), 1, glm::value_ptr(v));
}