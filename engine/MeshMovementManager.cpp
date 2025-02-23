
#include "MeshMovementManager.h"

void MeshMovementManager::setActiveMesh(Mesh* mesh) {
    if (m_isMoving) return;
    // Shallow comparision OK
    if (m_currentActiveMesh == mesh) return;

    if (m_currentActiveMesh) {
        m_currentActiveMesh->getMaterial()->resetEmissionFromBackup();
    }
    m_currentActiveMesh = mesh;
    m_currentActiveMesh->getMaterial()->setEmissionBackup();
    m_blinking = 0.0f;
}

void MeshMovementManager::setMovement(float limit, float speed) {
    if (!m_isMoving) {
        m_limit = limit;
        m_speed = speed;
        m_isMoving = true;
    }
}

bool MeshMovementManager::isMoving() {
    return m_isMoving;
}

void MeshMovementManager::blink() {
    if (!m_currentActiveMesh) return;

    if (m_blinking >= 1) m_blinking = 0.0f;
    else m_blinking += 0.01f;
    m_currentActiveMesh->getMaterial()->blinkEmission(m_blinking);
}

float MeshMovementManager::getLimit() {
    return m_limit;
}

void MeshMovementManager::reset() {
    m_currentActiveMesh = nullptr;
    m_blinking = 0.0f;
    m_limit = 0.0f;
    m_speed = 0.0f;
    m_isMoving = false;
}

void MeshMovementManager::moveActiveMesh() {
    if (m_limit > 0.0 && m_currentActiveMesh && m_isMoving) {
        m_limit -= m_speed < 0 ? -m_speed : m_speed;
        m_currentActiveMesh->translate(glm::vec3(0.0f, m_speed, 0.0f));
        if (m_limit <= 0.0) m_isMoving = false;
    }
}

Mesh* MeshMovementManager::getActiveMesh() {
    return m_currentActiveMesh; 
}


