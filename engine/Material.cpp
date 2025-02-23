// In questa classe si caricano i setting dei materialî
// Render material
// Material settings

#include "Material.h"
// FreeGLUT:   
#include <GL/freeglut.h>

Material::Material(const std::string& name)
    : Object("Material", name) {}

void Material::rendering(const glm::mat4& inverse_camera) const {
    if (m_texture && m_texture->checkBitmapExistence()) m_texture->rendering(inverse_camera);
    loadMaterialSettings();
}

void Material::loadMaterialSettings() const {
    const MaterialSettings& m = m_materialSettings; // just for shorter name
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, glm::value_ptr(glm::vec4(m.emission.r, m.emission.g, m.emission.b, m.alpha)));
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(glm::vec4(m.ambient.r, m.ambient.g, m.ambient.b, m.alpha)));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(glm::vec4(m.diffuse.r, m.diffuse.g, m.diffuse.b, m.alpha)));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(glm::vec4(m.specular.r, m.specular.g, m.specular.b, m.alpha)));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m.shininess);
}


void Material::setTexture(const std::shared_ptr<Texture>& texture) {
    this->m_texture = texture;
}

void Material::setMaterialSettings(const glm::vec4& emission, float shininess, const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, float alpha) {
    m_materialSettings.emission = emission;
    m_materialSettings.shininess = shininess;
    m_materialSettings.ambient = ambient;
    m_materialSettings.diffuse = diffuse;
    m_materialSettings.specular = specular;
    m_materialSettings.alpha = alpha;
}

MaterialSettings Material::getMaterialSettings() const {
    return m_materialSettings;
}

void Material::blinkEmission(float blinking) {
    m_materialSettings.emission.r = blinking;
    m_materialSettings.emission.g = blinking;
    m_materialSettings.emission.b = blinking;
}

void Material::setEmissionBackup() {
    m_materialSettings.emissionBackup = m_materialSettings.emission;
}

void Material::resetEmissionFromBackup() {
    m_materialSettings.emission = m_materialSettings.emissionBackup;
}


bool Material::isTexturePresent() const {
    return m_texture != nullptr;
}
