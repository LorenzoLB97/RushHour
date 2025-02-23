#include "../PointLight.h"
#include <cassert>

void testPointLightMethods() {
    // Creazione della luce puntiforme di test
    PointLight pointLight("TestPointLight");

    // Verifica dell'ID, del tipo e del nome
    assert(pointLight.getID() == 10);
    assert(pointLight.getType() == "PointLight");
    assert(pointLight.getName() == "TestPointLight");

    // Verifica del numero di luce
    assert(pointLight.getLightNumber() == 0);

    // Verifica delle impostazioni della luce
    pointLight.setLightAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    pointLight.setLightDiffuse(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
    pointLight.setLightSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    pointLight.setColor(glm::vec3(1.0f, 0.0f, 0.0f));

    // Verifica della posizione della luce puntiforme
    pointLight.setPosition(glm::vec3(10.0f, 5.0f, 3.0f));
    glm::vec3 position = pointLight.getPosition();
    assert(position.x == 10.0f);
    assert(position.y == 5.0f);
    assert(position.z == 3.0f);
}

