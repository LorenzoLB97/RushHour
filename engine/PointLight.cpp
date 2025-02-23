#include "PointLight.h"
#include <GL/freeglut.h>

PointLight::PointLight(const std::string& type)
    : Light{ "PointLight", type }
{
}

glm::vec3 PointLight::getPosition() const {
    return position;
}

void PointLight::setPosition(glm::vec3 position) {
    this->position = position;
}

void PointLight::rendering(const glm::mat4& cameraInv) const {
    glLoadMatrixf(glm::value_ptr(cameraInv * m_globalMatrix));

    // small emissive sphere to show light position:   
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(1.0f)));
    glutSolidSphere(3.0f, 8, 8);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(0.0f)));
    
    glLightfv(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_POSITION, (GLfloat*)glm::value_ptr(glm::vec4(position, 1.0f)));
    glLightfv(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_SPOT_CUTOFF, (GLfloat*) &cutoff);

    // Render rest of light
    Light::rendering(cameraInv);
}


