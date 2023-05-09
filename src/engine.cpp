#include <engine.hpp>

Engine::Engine()
{
    isWireframe = false;
    isErr = false;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    current = nullptr;
}

Engine::~Engine()
{
    for(uint i = 0; i < windowList.size(); i++)
    {
        delete windowList[i];
    }

    for(uint i = 0; i < shaderList.size(); i++) this->eraseShader(i);
    for(uint i = 0; i < vaoList.size(); i++) this->eraseBufferElement(i);
    glfwTerminate();
}

bool Engine::isError() { return isErr; }
std::string Engine::getError() { return errstring; }

void Engine::createWindow(const std::string& name, int width, int height)
{
    windowList.push_back(new Window(name, width, height));

    if(windowList.back()->isError())
    {
        isErr = true;
        errstring = windowList.back()->getError();
    }
}

void Engine::eraseWindow(uint idx) 
{ 
    delete this->getWindow(idx);
    windowList.erase(windowList.begin()+idx);
}
void Engine::eraseWindow(const std::string& name) 
{ 
    int idx = this->getVecWinPos(name);
    if(idx==-1) return;
    Window* ptr = this->getWindow(idx);
    if(current==ptr) current = nullptr;
    delete ptr;
    windowList.erase(windowList.begin()+idx);
}

Window* Engine::getWindow(uint idx) { return windowList[idx]; }
Window* Engine::getWindow(const std::string& name)
{
    for(uint i = 0; i < windowList.size(); i++)
    {
        if(windowList[i]->getName()==name)
        {
            return windowList[i];
        }
    }
    return nullptr;
}
int Engine::getVecWinPos(const std::string& name)
{
    for(uint i = 0; i < windowList.size(); i++)
    {
        if(windowList[i]->getName()==name)
        {
            return i;
        }
    }
    return -1;
}

void Engine::setMain(uint idx) 
{ 
    getWindow(idx)->setCurrent(); 
    current = getWindow(idx); 
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        isErr = true;
        errstring = "unknown GLAD error";
        return;
    }
    glViewport(0, 0, current->getWidth(), current->getHeight());
}
void Engine::setMain(const std::string& name) 
{ 
    Window* tempWin = getWindow(name); 
    if(tempWin==nullptr) return;
    tempWin->setCurrent(); 
    current = tempWin;

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        isErr = true;
        errstring = "unknown GLAD error";
        return;
    }

    glViewport(0, 0, current->getWidth(), current->getHeight());
}

void Engine::createShader(const std::string& vertsrc, const std::string& fragsrc, const std::string& geomsrc) { shaderList.push_back(new Shader(vertsrc, fragsrc, geomsrc)); }
void Engine::createShader(const std::filesystem::path& vertpath, const std::filesystem::path& fragpath, const std::filesystem::path& geompath) { shaderList.push_back(new Shader(vertpath, fragpath, geompath)); }
Shader* Engine::getShader(uint idx) { return shaderList[idx]; }
void Engine::eraseShader(uint idx) { delete shaderList[idx]; shaderList.erase(shaderList.begin()+idx); }

void Engine::useShader(uint idx) { shaderList[idx]->use(); }
bool Engine::isShaderValid(uint idx) { return shaderList[idx]->isShaderValid(); }

void Engine::createBufferElement(const std::vector<float>& data, const std::vector<attribDescriptor>& attributes) {
    VBO* vbo = new VBO(data);
    VAO* vao = new VAO(vbo, attributes);
    vaoList.push_back(vao);
}

void Engine::createBufferElement(const std::vector<float>& data, const std::vector<uint>& indices, const std::vector<attribDescriptor>& attributes) {
    VBO* vbo = new VBO(data);
    EBO* ebo = new EBO(indices);
    VAO* vao = new VAO(vbo, ebo, attributes);
    vaoList.push_back(vao);
}

VAO* Engine::getBufferElement(uint idx) {
    return vaoList[idx];
}

void Engine::eraseBufferElement(uint idx) {
    delete vaoList[idx];
    vaoList.erase(vaoList.begin()+idx);
}

void Engine::toggleWireframeMode() {
    if(isWireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        isWireframe = false;
    }
    else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        isWireframe = true;
    }
}

Window* Engine::getCurrentWin() { return current; }

void Engine::pollEvents() { glfwPollEvents(); }
void Engine::update()
{
    for(uint i = 0; i < windowList.size(); i++)
    {
        windowList[i]->update();
    }
}