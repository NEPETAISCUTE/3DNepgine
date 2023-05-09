#include <iostream>
#include <time.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <engine.hpp>
#include <camera.hpp>

const float PI = 3.1415926535897932384626433832795028841971;

std::vector<float> vertices = {
    0.5, 0.5, 0.5,    1.0, 1.0,
    -0.5, 0.5, 0.5,     0.0, 1.0,
    0.5, -0.5, 0.5,    1.0, 0.0,
    0.5, -0.5, 0.5,    1.0, 0.0,
    -0.5, -0.5, 0.5,   0.0, 0.0,
    -0.5, 0.5, 0.5,    0.0, 1.0,

    0.5, 0.5, -0.5,    1.0, 1.0,
    -0.5, 0.5, -0.5,     0.0, 1.0,
    0.5, -0.5, -0.5,    1.0, 0.0,
    0.5, -0.5, -0.5,    1.0, 0.0,
    -0.5, -0.5, -0.5,   0.0, 0.0,
    -0.5, 0.5, -0.5,    0.0, 1.0,

    0.5, 0.5, 0.5,    1.0, 1.0,
    0.5, 0.5, -0.5,     0.0, 1.0,
    0.5, -0.5, 0.5,    1.0, 0.0,
    0.5, -0.5, 0.5,    1.0, 0.0,
    0.5, -0.5, -0.5,   0.0, 0.0,
    0.5, 0.5, -0.5,    0.0, 1.0,

    -0.5, 0.5, 0.5,    1.0, 1.0,
    -0.5, 0.5, -0.5,     0.0, 1.0,
    -0.5, -0.5, 0.5,    1.0, 0.0,
    -0.5, -0.5, 0.5,    1.0, 0.0,
    -0.5, -0.5, -0.5,   0.0, 0.0,
    -0.5, 0.5, -0.5,    0.0, 1.0,

    0.5, 0.5, 0.5,    1.0, 1.0,
    0.5, 0.5, -0.5,     0.0, 1.0,
    -0.5, 0.5, 0.5,    1.0, 0.0,
    -0.5, 0.5, 0.5,    1.0, 0.0,
    -0.5, 0.5, -0.5,   0.0, 0.0,
    0.5, 0.5, -0.5,    0.0, 1.0,

    0.5, -0.5, 0.5,    1.0, 1.0,
    0.5, -0.5, -0.5,     0.0, 1.0,
    -0.5, -0.5, 0.5,    1.0, 0.0,
    -0.5, -0.5, 0.5,    1.0, 0.0,
    -0.5, -0.5, -0.5,   0.0, 0.0,
    0.5, -0.5, -0.5,    0.0, 1.0,
};

std::vector<glm::vec3> cubePos = {
  glm::vec3(2.0, 2.0, 2.0),
  glm::vec3(5.0, -1.0, -2.0),
  glm::vec3(2.0, 2.0, -2.0),
  glm::vec3(-7.0, 2.0, 27.0),
  glm::vec3(1.0, 5.0, 17.0),
  glm::vec3(-8.0, -5.0, 2.0)
};

static double lastX = 0;
static double lastY = 0;
static bool firstMouse = true;

static double yaw, pitch;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
}  

static float deltaTime = 0.0;
static float lastFrame = 0.0;

void processInput(Window* w, Camera* c)
{
    GLFWwindow* win = w->getPtr();
    glm::vec3 camPos = c->getPos();
    glm::vec3 camFront = c->getFront();
    glm::vec3 camUp = c->getUp();
    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        c->setPos(camPos+cameraSpeed*camFront);
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        c->setPos(camPos-cameraSpeed*camFront);
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        c->setPos(camPos-glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed); //-= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        c->setPos(camPos+glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed); //cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(win, GLFW_KEY_SPACE) == GLFW_PRESS)
        c->setPos(camPos+glm::normalize(camUp) * cameraSpeed);
    if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        c->setPos(camPos-glm::normalize(camUp) * cameraSpeed);
    if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        w->close();
}

std::vector<attribDescriptor> attribs;



static Engine* e;

int main() {

/*
{
uint sideNum = 3;
std::vector<glm::vec3> tempVert = {{0, 0, 0}};
for(uint i=0; i<sideNum; i++){
  float angle = (PI*2)/sideNum;
  tempVert.emplace_back(std::cos(angle*i)*0.5, -0.5, std::sin(angle*i)*0.5);
}

std::vector<uint> tempIndeces /*= {0, 1, 2, 0, 2, 3, 0, 3, 1, 1, 2, 3}*//*;
for(uint i =0; i< sideNum; i++){
  tempIndeces.push_back(0);
  tempIndeces.push_back(i+1);
  tempIndeces.push_back(((i+2)==(sideNum+1))? 1 : i+2);
}


vertices.clear();
for(uint i=0; i<tempIndeces.size(); i++){
  vertices.push_back(tempVert[tempIndeces[i]].x);
  vertices.push_back(tempVert[tempIndeces[i]].y);
  vertices.push_back(tempVert[tempIndeces[i]].z);
  switch(i%3){
    default:
    case 0:
      vertices.push_back(0.5);
      vertices.push_back(0);
      break;
    case 1:
      vertices.push_back(0);
      vertices.push_back(1);
      break;
    case 2:
      vertices.push_back(1);
      vertices.push_back(1);
      break;
  }
}

for(uint i = 2; i<sideNum; i++){
  float angle = (PI*2)/sideNum;
  vertices.push_back(tempVert[1].x);
  vertices.push_back(tempVert[1].y);
  vertices.push_back(tempVert[1].z);
  vertices.push_back(0.5+std::cos(angle*0)*0.5);
  vertices.push_back(0.5+std::sin(angle*0)*0.5);

  vertices.push_back(tempVert[i].x);
  vertices.push_back(tempVert[i].y);
  vertices.push_back(tempVert[i].z);
  vertices.push_back(0.5+std::cos(angle*i)*0.5);
  vertices.push_back(0.5+std::sin(angle*i)*0.5);

  vertices.push_back(tempVert[i+1].x);
  vertices.push_back(tempVert[i+1].y);
  vertices.push_back(tempVert[i+1].z);
  vertices.push_back(0.5+std::cos(angle*(i+1))*0.5);
  vertices.push_back(0.5+std::sin(angle*(i+1))*0.5);
}

}
*/
    e = new Engine();

    e->createWindow("testwin", 800, 600);
    e->setMain(0);

    glEnable(GL_DEPTH_TEST);

    std::filesystem::path vertpath = "./shaders/shader.vs";
    std::filesystem::path fragpath = "./shaders/shader.fs";
    e->createShader(vertpath, fragpath);

    fragpath = "./shaders/lightsource.fs";
    e->createShader(vertpath, fragpath);

    attribs.push_back(attribDescriptor(3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)NULL));
    attribs.push_back(attribDescriptor(2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float))));

    e->createBufferElement(vertices, attribs);

    Texture* t = new Texture("./res/tex/SPOILER_KittyCat.png", GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Window* w = e->getCurrentWin();
    w->setInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    w->setCursorCallback(mouse_callback);

    Camera* c = new Camera(45.0f, 800, 600, 0.1, 100.0);
    c->setPos(glm::vec3(0.0f, 0.0f, 3.0f));
    c->setFront(glm::vec3(0.0f, 0.0f, -1.0f));
    c->setUp(glm::vec3(0.0, 1.0, 0.0));
    const float radius = 10.0f;
    Shader* s = e->getShader(0);
    while(!w->shouldClose())
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame; 
        processInput(w, c);
        c->setAngle(yaw, pitch);
        c->lookAt();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        e->getBufferElement(0)->bind();
        for(int i = 0; i < cubePos.size(); i++)
        {
          glm::mat4 trans(1.0);
          trans = glm::translate(trans, cubePos[i]);
          trans = glm::rotate(trans, (float)glfwGetTime()*(i+1), glm::vec3(1.0, 1.0, 1.0));

          s->use();
          uint modelLoc = glGetUniformLocation(s->getProg(), "model");
          glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(trans));
          glUniformMatrix4fv(glGetUniformLocation(s->getProg(), "view"), 1, GL_FALSE, glm::value_ptr(c->getView()));
          glUniformMatrix4fv(glGetUniformLocation(s->getProg(), "projection"), 1, GL_FALSE, glm::value_ptr(c->getProj()));
          glDrawArrays(GL_TRIANGLES, 0, vertices.size()/5);
        }
        /*s->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        s->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()/5);*/


        if(glfwGetKey(w->getPtr(), GLFW_KEY_Z) == GLFW_PRESS) e->toggleWireframeMode();
        e->update();
        glfwPollEvents();

    }

    delete t;
    delete e;
    return 0;
}
    
