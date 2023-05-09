#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <iostream>
#include <array>
#include <vector>
#include <filesystem>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <window.hpp>
#include <shader.hpp>
#include <vao.hpp>
#include <vbo.hpp>
#include <texture.hpp>


class Engine {
    Window* current;
    std::vector<Window*> windowList;

    std::vector<Shader*> shaderList;

    std::vector<VAO*> vaoList;

    bool isWireframe;

    bool isErr;
    std::string errstring;
public:
    Engine();
    Engine(const std::string& name, int width, int height);
    ~Engine();

    bool isError();
    std::string getError();

    void createWindow(const std::string& name, int width, int height);
    void eraseWindow(uint idx);
    void eraseWindow(const std::string& name);

    Window* getWindow(uint idx);
    Window* getWindow(const std::string& name);
    int getVecWinPos(const std::string& name);
    Window* getCurrentWin();

    void setMain(uint idx);
    void setMain(const std::string& name);

    void createShader(const std::string& vertsrc, const std::string& fragsrc, const std::string& geomsrc="");
    void createShader(const std::filesystem::path& vertpath, const std::filesystem::path& fragpath, const std::filesystem::path& geompath="");

    Shader* getShader(uint idx);
    void eraseShader(uint idx);

    void createBufferElement(const std::vector<float>& data, const std::vector<attribDescriptor>& attributes);
    void createBufferElement(const std::vector<float>& data, const std::vector<uint>& indices, const std::vector<attribDescriptor>& attributes);
    VAO* getBufferElement(uint idx);

    void eraseBufferElement(uint idx);

    void toggleWireframeMode();

    void useShader(uint idx);
    bool isShaderValid(uint idx);

    void pollEvents();
    void update();
};
#endif