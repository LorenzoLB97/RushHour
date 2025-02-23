#include "PrimaryCamera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/freeglut.h>


Camera::Camera(const std::string& name) : Node{ name, "Camera" } {
    setInitialPosition();
}

void Camera::setInitialPosition() {
    m_atX = -5.0f;
    m_atY = 141.0f;
    m_angleX = m_angleY = m_angleZ = 0.0f;
    m_eyeX = 0.0f;
    m_eyeY = -3.0f;
    m_eyeZ = 3.0f;
    m_distance = 150.0f;

    m_staticCameraLookAt = glm::lookAt(glm::vec3(0.0f, -44.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_staticCamera = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 254.0f, 63.0f)) * m_staticCameraLookAt;
	reloadDynamicCamera();
}

void Camera::setSpeedMovement(float speed) {
    this->m_speed = speed;
}

void Camera::switchCamera() {
    m_isDynamic = !m_isDynamic;
    m_currentCamera = m_isDynamic ? m_dynamicCamera : m_staticCamera;
}

void Camera::to3dMode() const {
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(value_ptr(m_projMatrix));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(value_ptr(m_currentCamera));
}

void Camera::to2dMode() const {
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(m_orthoMatrix));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(glm::mat4(1.0f)));
}

void Camera::moveForward() {
	m_distance -= m_speed;
	reloadDynamicCamera();

}

void Camera::moveBackwards() {
	m_distance += m_speed;
	reloadDynamicCamera();

}

void Camera::moveLeft() {
	m_atX -= m_speed;
	reloadDynamicCamera();

}

void Camera::moveRight() {
	m_atX += m_speed;
	reloadDynamicCamera();

}

void Camera::moveUp() {
	m_atY += m_speed;
	reloadDynamicCamera();

}

void Camera::moveDown() {
	m_atY -= m_speed;
	reloadDynamicCamera();

}

void Camera::lookUp() {
	m_angleX += m_speed;
	reloadDynamicCamera();

}

void Camera::lookDown() {
	m_angleX -= m_speed;
	reloadDynamicCamera();

}

void Camera::lookLeft() {
	m_angleY += m_speed;
	reloadDynamicCamera();

}

void Camera::lookRight() {
	m_angleY -= m_speed;
	reloadDynamicCamera();

}

void Camera::rotateLeft() {
	m_angleZ += m_speed;
	reloadDynamicCamera();
}

void Camera::rotateRight() {
	m_angleZ -= m_speed;
	reloadDynamicCamera();
}

void Camera::loadProjectionMatrix() {
	glLoadMatrixf(glm::value_ptr(m_projMatrix));
}

glm::mat4 Camera::setProjectionMatrix(float width, float height) {
	m_projMatrix = glm::perspective(glm::radians(m_fov), width / height, m_nearPlane, m_farPlane);
	return m_projMatrix;
}

glm::mat4 Camera::getCameraInverse() const {
	return glm::inverse(m_currentCamera);
}


void Camera::reloadDynamicCamera() {
    auto rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(this->m_angleX), glm::vec3(1.0f, 0.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(this->m_angleY), glm::vec3(0.0f, 1.0f, 0.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(this->m_angleZ), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec3 eye = glm::vec3(m_eyeX, m_eyeY, m_eyeZ);
	glm::vec3 center{};
	glm::vec3 up(0.0f, 1.0f, 0.0f);
    m_dynamicCameraLookAt = glm::lookAt(eye, center, glm::vec3(0.0f, 1.0f, 0.0f));
    m_dynamicCamera = glm::translate(glm::mat4(1.0f), glm::vec3(m_atX, m_atY, m_distance)) * m_dynamicCameraLookAt * rotationMatrix;
    m_currentCamera = m_isDynamic ? m_dynamicCamera : m_staticCamera;
}

glm::mat4 Camera::getOrthogonalMatrix() const {
    return m_orthoMatrix;
}

void Camera::setOrthogonalMatrix(const glm::mat4& orthogonalMatrix) {
    m_orthoMatrix = orthogonalMatrix;
}

bool Camera::isDynamic() {
	return m_isDynamic;
}
float Camera::getSpeedMovement() {
	return m_speed;
}
float Camera::getAngleX() {
	return m_angleX;
}
float Camera::getAngleY() {
	return m_angleY;
}
float Camera::getAngleZ() {
	return m_angleZ;
}
float Camera::getDistance() {
	return m_distance;
}
float Camera::getEyeX() {
	return m_eyeX;
}
float Camera::getEyeY() {
	return m_eyeY;
}
float Camera::getEyeZ() {
	return m_eyeZ;
}
float Camera::getAtX() {
	return m_atX;
}
float Camera::getAtY(){
	return m_atY;
}
glm::mat4 Camera::getProjectionMatrix(){
	return m_projMatrix;
}