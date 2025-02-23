#include "SpotLight.h"

#include <GL/freeglut.h>

SpotLight::SpotLight(const std::string& name)
    : Light{ "SpotLight", name }
{
}


void SpotLight::setDirection(const glm::vec3& lightDirection) {
	direction = lightDirection;
}

void SpotLight::setLightCutoff(float lightCutoff) {
	cutOff = lightCutoff;
}

float SpotLight::getLightCutoff() const {
	return cutOff;
}

glm::vec3 SpotLight::getDirection() const {
	return direction;
}

void SpotLight::spotExponent(float exponent) {
	this->exponent = exponent;
}

void SpotLight::rendering(const glm::mat4& cameraInv) const {
    glLoadMatrixf(glm::value_ptr(cameraInv * m_globalMatrix));

    glLightfv(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_POSITION, (GLfloat*)glm::value_ptr(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)));
    glLightf(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_SPOT_CUTOFF, static_cast<GLfloat>(cutOff));
    glLightf(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_SPOT_EXPONENT, static_cast<GLfloat>(exponent));
    glm::vec3 normalizedDirection = glm::normalize(direction);
    glLightfv(static_cast<GLenum>(GL_LIGHT0 + m_lightNum), GL_SPOT_DIRECTION, (GLfloat*)glm::value_ptr(normalizedDirection));

    // Render rest of light
    Light::rendering(cameraInv);
}

float SpotLight::getSpotExponent() const {
    return exponent;
}
