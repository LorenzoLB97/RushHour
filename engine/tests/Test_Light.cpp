#include "../Light.h"
#include <cassert>

void testLightMethods() {
    // Creazione della luce di test
    Light testLight("PointLight", "TestLight");

    // Verifica dell'ID, del tipo e del nome
    assert(testLight.getID() == 2);
    assert(testLight.getType() == "PointLight");
    assert(testLight.getName() == "TestLight");

    // Verifica del numero di luce
    assert(testLight.getLightNumber() == 0);
}
