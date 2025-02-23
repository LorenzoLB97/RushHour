#include "Mesh.h"
#include <glm/gtc/packing.hpp>
#include <GL/freeglut.h>


Mesh::Mesh(const std::string& name) : Node{ "Mesh", name} {}


void Mesh::setMaterial(const std::shared_ptr<Material>& material) {
	m_material = material;
}

void Mesh::setLodInfo(const std::vector<LodData>& lodInfo) {
	m_LodInfo = lodInfo;
}

void Mesh::rendering(const glm::mat4& camera) const {
    m_material->rendering(camera);
    glLoadMatrixf(value_ptr(camera * m_globalMatrix));

    if (!renderColorsOnly) {
        renderMesh();
        renderShadowMesh(camera);
    } else {     
        renderMeshColorOnly();
    }
}


void Mesh::renderMesh() const {
    const LodData accurateLod = m_LodInfo[0];
    const bool isTexturePresent = m_material->isTexturePresent();

    if (getName() == "Teapot001") {
        glDisable(GL_CULL_FACE);
    }
    else {
        glEnable(GL_CULL_FACE);
    }
   
    if (isTexturePresent) 
        glEnable(GL_TEXTURE_2D);
    
    for (const auto& face : accurateLod.faces) {
        glBegin(GL_TRIANGLES);
        for (const auto& coord : face) {
            const VertexData& vertex = accurateLod.vertices[coord];
            glNormal3fv(glm::value_ptr(glm::normalize(vertex.normal)));
            glTexCoord2fv(glm::value_ptr(vertex.textureData));
            glVertex3f(vertex.vertex.x, vertex.vertex.y, vertex.vertex.z);
        }
        glEnd();
    }

    if (isTexturePresent) 
        glDisable(GL_TEXTURE_2D);
}

void Mesh::renderShadowMesh(const glm::mat4& camera) const {
    glm::mat4 shadowMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    glLoadMatrixf(value_ptr(camera * m_globalMatrix * shadowMatrix));

    const LodData accurateLod = m_LodInfo[0];

    glDisable(GL_LIGHTING);
    for (const auto& face : accurateLod.faces) {
        glBegin(GL_TRIANGLES);
        for (const auto& coord : face) {
            const VertexData& vertex = accurateLod.vertices[coord];
            glNormal3fv(glm::value_ptr(glm::normalize(vertex.normal)));
            glColor3f(0.0f, 0.0f, 0.0f);
            glVertex3f(vertex.vertex.x, vertex.vertex.y, vertex.vertex.z);
        }
        glEnd();
    }
    glEnable(GL_LIGHTING);
}


void Mesh::renderMeshColorOnly() const {
    const LodData accurateLod = m_LodInfo[0];

    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    for (const auto& face : accurateLod.faces) {
        glBegin(GL_TRIANGLES);
        for (const auto& coord : face) {
            const VertexData& vertex = accurateLod.vertices[coord];
            const auto color = generateUniqueColor();
            GLubyte uniqueColor[4] = { (GLubyte)color.r, (GLubyte)color.g, (GLubyte)color.b, (GLubyte)color.a };
            glColor4ubv(uniqueColor);
            glVertex3f(vertex.vertex.x, vertex.vertex.y, vertex.vertex.z);
        }
        glEnd();
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}
