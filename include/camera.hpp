#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
    glm::mat4 view;
    glm::mat4 proj;

    glm::vec3 pos;
    glm::vec3 up;
    glm::vec3 front;
public:
    Camera(float left, float right, float bottom, float top, float near, float far);
    Camera(float fov, uint width, uint height, float near, float far);

    void setPos(glm::vec3 pos);
    void setFront(glm::vec3 front);
    void setUp(glm::vec3 up);

    void setAngle(float yaw, float pitch);

    glm::vec3 getPos();
    glm::vec3 getFront();
    glm::vec3 getDirection();
    glm::vec3 getUp();
    void lookAt(glm::vec3 pos, glm::vec3 direction, glm::vec3 up);
    void lookAt();

    glm::mat4 getView();
    glm::mat4 getProj();
    void setView(glm::mat4 view);

    void translate(glm::vec3 vector);
    void translate(float x, float y, float z);
};

#endif