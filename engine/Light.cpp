#include "Light.h"
#include "Object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/freeglut.h>


Light::Light(const std::string& type, const std::string& name)
    : Node{ type, name } 
{
    m_lightNum = totLights;
    ++totLights;
}

Light::~Light() {
    --totLights;
}

void Light::enableLights() {
    //glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f);
}

void Light::setLightAmbient(glm::vec4 lightAmbient) {
    this->m_lightAmbient = lightAmbient;
}

void Light::setLightDiffuse(glm::vec4 lightDiffuse) {
    this->m_lightDiffuse = lightDiffuse;
}

void Light::setLightSpecular(glm::vec4 lightSpecular) {
    this->m_lightSpecular = lightSpecular;
}

std::size_t Light::getLightNumber() const {
    return m_lightNum;
}

void Light::rendering(const glm::mat4& cameraInv) const {
    glEnable(static_cast<GLenum>(GL_LIGHT0 + m_lightNum));

    // Light color
    GLfloat diffuse[] = { m_lightColor.r, m_lightColor.g, m_lightColor.b, 1.0f };
    glLightfv(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_DIFFUSE, (GLfloat*)diffuse);

    glLightfv(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_AMBIENT, (GLfloat*)glm::value_ptr(m_lightAmbient));
    glLightfv(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_SPECULAR, (GLfloat*)glm::value_ptr(m_lightSpecular));

    glLightf(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_LINEAR_ATTENUATION, 0.0f);
    glLightf(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_QUADRATIC_ATTENUATION, 0.0f);

    glm::vec4 gAmbient(0.2f, 0.2f, 0.2f, 1.0f);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, (GLfloat*)glm::value_ptr(gAmbient));
}

void Light::setColor(const glm::vec3& color) {
    this->m_lightColor = color;
}
