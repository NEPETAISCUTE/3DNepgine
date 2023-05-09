#include <camera.hpp>

Camera::Camera(float left, float right, float bottom, float top, float near, float far)
{
    proj = glm::ortho(left, right, bottom, top, near, far);
    view = glm::mat4(1.0f);
// note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    setAngle(90.0, 90.0);
}

Camera::Camera(float fov, uint width, uint height, float near, float far)
{
    proj = glm::perspective(glm::radians(fov), (float)width/(float)height, near, far);
    view = glm::mat4(1.0f);
    setAngle(90.0, 90.0);
}

void Camera::setPos(glm::vec3 pos) { this->pos = pos; }
void Camera::setFront(glm::vec3 front) { this->front = front; }
void Camera::setUp(glm::vec3 up) { this->up = up; }

glm::vec3 Camera::getPos() { return pos; }
glm::vec3 Camera::getFront() { return front; }
glm::vec3 Camera::getUp() { return up; }

void Camera::setAngle(float yaw, float pitch)
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(direction);
}

void Camera::lookAt() { view = glm::lookAt(pos, pos+front, up); }
void Camera::lookAt(glm::vec3 pos, glm::vec3 front, glm::vec3 up)
{
    this->pos = pos;
    this->front = front;
    this->up = up;

    view = glm::lookAt(pos, pos + front, up);
}

glm::mat4 Camera::getProj() { return proj; }
glm::mat4 Camera::getView() { return view; }
void Camera::setView(glm::mat4 view) { this->view = view; }