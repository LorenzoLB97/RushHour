#include "DirectionalLight.h"
#include <GL/freeglut.h>

DirectionalLight::DirectionalLight(const std::string& name) 
    : Light{ "DirectionalLight", name } 
{
}

void DirectionalLight::rendering(const glm::mat4& cameraInv) const {
    glLoadMatrixf(glm::value_ptr(cameraInv * m_globalMatrix));

    glLightfv(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_POSITION, (GLfloat*)(glm::value_ptr(glm::vec4(m_direction.x, m_direction.y, m_direction.z, 0.0f))));

    // Render rest of light
    Light::rendering(cameraInv);
}

glm::vec3 DirectionalLight::getDirection() const {
    return m_direction;
}
void DirectionalLight::setDirection(glm::vec3 direction) {
    m_direction = direction;
}
