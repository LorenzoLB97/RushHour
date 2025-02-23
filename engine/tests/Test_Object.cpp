#include "../Object.h"
#include <cassert>

class TestObject : public Object {
public:
    TestObject(const std::string& type, const std::string& name)
        : Object(type, name) {}

    // Implementazione del metodo virtuale puro
    void rendering(const glm::mat4& inverse_camera) const override {}
};

void testObjectMethods() {
    // Creazione di un oggetto di test
    TestObject testObject("ObjectType", "ObjectName");

    // Verifica dell'ID, del tipo e del nome
    assert(testObject.getID() == 8);
    assert(testObject.getType() == "ObjectType");
    assert(testObject.getName() == "ObjectName");

    // Cambio del tipo e verifica
    testObject.setType("NewType");
    assert(testObject.getType() == "NewType");

    // Verifica della generazione di un colore univoco
    glm::vec4 uniqueColor = testObject.generateUniqueColor();
    assert(uniqueColor.r == 8 && uniqueColor.g == 8 && uniqueColor.b == 8 && uniqueColor.a == 255);

    // Creazione di un secondo oggetto di test
    TestObject testObject2("ObjectType", "ObjectName2");

    // Verifica dell'ID, del tipo e del nome
    assert(testObject2.getID() == 9);
    assert(testObject2.getName() == "ObjectName2");

    // Verifica della generazione di un colore univoco per il secondo oggetto
    glm::vec4 uniqueColor2 = testObject2.generateUniqueColor();
    assert(uniqueColor2.r == 9 && uniqueColor2.g == 9 && uniqueColor2.b == 9 && uniqueColor2.a == 255);
}

