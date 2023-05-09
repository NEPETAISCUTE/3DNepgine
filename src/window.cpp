#include <window.hpp>

Window::Window(const std::string& name, int width, int height)
{
    this->name = name;
    this->width = width;
    this->height = height;
    error = GLFW_NO_ERROR;

    ptr = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
    if( ptr==nullptr )
    {
        const char* temperrstring;
        error = glfwGetError(&temperrstring);
        errorstring = temperrstring;
    }
}   

Window::~Window() { glfwDestroyWindow(ptr); }

bool Window::isError() { return error!=GLFW_NO_ERROR; }
std::string Window::getError() { return "Window error: "+error+'\n'+errorstring;}

GLFWwindow* Window::getPtr() { return ptr; }
std::string Window::getName() { return name; }
int Window::getWidth() { return width; }
int Window::getHeight() { return height; }

void Window::resize(int width, int height)
{
    this->width = width;
    this->height = height;

    glViewport(0, 0, width, height);
}

int Window::shouldClose() { return glfwWindowShouldClose(ptr); }
void Window::close() { glfwSetWindowShouldClose(ptr, true); }
void Window::update() { glfwSwapBuffers(ptr); }
void Window::setCurrent() 
{ 
    glfwMakeContextCurrent(ptr); 
}

void Window::setInputMode(uint type, uint value)
{
    glfwSetInputMode(getPtr(), type, value);  
}

void Window::setCursorCallback(void mouse_callback(GLFWwindow* window, double xpos, double ypos))
{
    glfwSetCursorPosCallback(getPtr(), mouse_callback);
}