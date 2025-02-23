#include "../SpotLight.h"
#include <cassert>

void testSpotLightMethods() {
    // Creazione della luce spot di test
    SpotLight spotLight("TestSpotLight");

    // Verifica dell'ID, del tipo e del nome
    assert(spotLight.getID() == 12);
    assert(spotLight.getType() == "SpotLight");
    assert(spotLight.getName() == "TestSpotLight");

    // Verifica del numero di luce
    assert(spotLight.getLightNumber() == 0);

    // Verifica delle impostazioni della luce
    spotLight.setLightAmbient(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
    spotLight.setLightDiffuse(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
    spotLight.setLightSpecular(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    spotLight.setColor(glm::vec3(1.0f, 0.0f, 0.0f));

    // Verifica della direzione della luce spot
    spotLight.setDirection(glm::vec3(-1.0f, -1.0f, -1.0f));
    glm::vec3 direction = spotLight.getDirection();
    assert(direction.x == -1.0f);
    assert(direction.y == -1.0f);
    assert(direction.z == -1.0f);

    // Verifica dell'angolo di taglio della luce spot
    spotLight.setLightCutoff(45.0f);
    assert(spotLight.getLightCutoff() == 45.0f);

    // Verifica dell'esponente della luce spot
    spotLight.spotExponent(20.0f);
    assert(spotLight.getSpotExponent() == 20.0f);
}
