#include "../PrimaryCamera.h"
#include <cassert>

void testCameraMethods() {
    // Creazione della camera di test
    Camera testCamera("TestCamera");

    // Verifica dell'ID, del tipo e del nome
    assert(testCamera.getID() == 11);
    assert(testCamera.getName() == "Camera");
    assert(testCamera.getType() == "TestCamera");

    // Verifica dell'impostazione iniziale della posizione
    testCamera.setInitialPosition();
    assert(testCamera.getAtX() == -5.0f);
    assert(testCamera.getAtY() == 141.0f);

    // Impostazione della velocità di movimento
    testCamera.setSpeedMovement(2.0f);
    assert(testCamera.getSpeedMovement() == 2.0f);

    // Verifica del cambio della camera
    assert(testCamera.isDynamic());
    testCamera.switchCamera();
    assert(!testCamera.isDynamic());

    // Movimenti e rotazioni
    testCamera.moveForward();
    assert(testCamera.getDistance() == 148.0f);

    testCamera.moveBackwards();
    assert(testCamera.getDistance() == 150.0f);

    testCamera.moveLeft();
    assert(testCamera.getAtX() == -7.0f);

    testCamera.moveRight();
    assert(testCamera.getAtX() == -5.0f);

    testCamera.moveUp();
    assert(testCamera.getAtY() == 143.0f);

    testCamera.moveDown();
    assert(testCamera.getAtY() == 141.0f);

    testCamera.lookUp();
    assert(testCamera.getAngleX() > 0.0f);

    testCamera.lookDown();
    assert(testCamera.getAngleX() == 0.0f);

    testCamera.lookLeft();
    assert(testCamera.getAngleY() > 0.0f);

    testCamera.lookRight();
    assert(testCamera.getAngleY() == 0.0f);

    testCamera.rotateLeft();
    assert(testCamera.getAngleZ() > 0.0f);

    testCamera.rotateRight();
    assert(testCamera.getAngleZ() == 0.0f);

    // Verifica della matrice di proiezione
    testCamera.setProjectionMatrix(800.0f, 600.0f);
    assert(testCamera.getProjectionMatrix() != glm::mat4(1.0f));

    // Verifica della matrice inversa
    assert(testCamera.getCameraInverse() != glm::mat4(1.0f));
}
