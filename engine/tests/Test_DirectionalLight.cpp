#include "../DirectionalLight.h"
#include <cassert>
#include <iostream>

void testDirectionalLightMethods() {
    // Creazione della luce direzionale di test
    DirectionalLight directionalLight("TestDirectionalLight");


    // Verifica dell'ID, del tipo e del nome
    assert(directionalLight.getID() == 1);
    assert(directionalLight.getType() == "DirectionalLight");
    assert(directionalLight.getName() == "TestDirectionalLight");

    // Verifica del numero di luce
    assert(directionalLight.getLightNumber() == 0);

    // Verifica della direzione della luce
    directionalLight.setDirection(glm::vec3(1.0f, 2.0f, 3.0f));
    glm::vec3 direction = directionalLight.getDirection();
    assert(direction.x == 1.0f);
    assert(direction.y == 2.0f);
    assert(direction.z == 3.0f);
}
