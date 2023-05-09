#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Window {
    GLFWwindow* ptr;
    std::string name;
    int width;
    int height;

    

    int error;
    std::string errorstring;

public:
    Window(const std::string& name, int width, int height);
    ~Window();

    bool isError();
    std::string getError();

    GLFWwindow* getPtr();
    std::string getName();
    int getWidth();
    int getHeight();
    void resize(int width, int height);

    int shouldClose();
    void close(); //glfwSetWindowShouldClose(window, true);
    void update();

    void setCurrent();

    void setInputMode(uint type, uint value);
    void setCursorCallback(void mouse_callback(GLFWwindow* window, double xpos, double ypos));
};
#endif