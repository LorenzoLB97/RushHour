
#include <iostream>
#include <utility> // std::move
#include <memory>  // smart pointers
#include "engine.h"
#include "GameLogic.h"
#include "PointLight.h"
#include "MeshMovementManager.h"


// We need these globals because we cannot pass i to the callback function
GameLogic gameLogic{ 1 };
PointLight* dynLight;
int gameEnded = false;


// We need to simulate the constants of FreeGLUT to use them in the client
namespace Constants {
    constexpr inline int MOUSE_LEFT_BUTTON = 0;
    constexpr inline int MOUSE_DOWN = 0;
    constexpr inline int KEYBOARD_KEY_UP = 101;
    constexpr inline int KEYBOARD_KEY_DOWN = 103;
    constexpr inline int KEYBOARD_KEY_LEFT= 100;
    constexpr inline int KEYBOARD_KEY_RIGHT= 102;
}

bool canAutoMoveVertically(const std::string& name) {
    const size_t pos = name.find("AutoV");
    return (pos != std::string::npos);
}

bool canAutoMoveHorizotally(const std::string& name) {
    const size_t pos = name.find("AutoL");
    return (pos != std::string::npos);
}

float getMovementDistanceByName(const std::string& name) {
    const size_t pos = name.find("G");
    if (pos != std::string::npos) return 14.0f;
    return 21.0f;
}

bool isAuto(const std::string& name) {
    const size_t pos = name.find("Auto");
    return (pos != std::string::npos);
}

void methodSpecialCallback(int key, int mouseX, int mouseY) {
    Engine& engine = Engine::getInstance();
    MeshMovementManager& meshManager = engine.getMeshManager();
    
    if (meshManager.getActiveMesh() && !meshManager.isMoving() && !gameEnded) {
        switch (key) {

        case Constants::KEYBOARD_KEY_UP:
            if (canAutoMoveVertically(meshManager.getActiveMesh()->getName()) &&
                gameLogic.moveAuto(meshManager.getActiveMesh()->getName(), Constants::KEYBOARD_KEY_UP)) {
                if (gameLogic.checkVictory()) {
                    meshManager.setMovement(getMovementDistanceByName(meshManager.getActiveMesh()->getName()) * 3);
                    gameEnded = true;
                    if (gameEnded) engine.switchGameEnd(true);
                }
                else meshManager.setMovement(getMovementDistanceByName(meshManager.getActiveMesh()->getName()), 1.0);
            }
            break;

        case Constants::KEYBOARD_KEY_DOWN:
            if (canAutoMoveVertically(meshManager.getActiveMesh()->getName()) &&
                gameLogic.moveAuto(meshManager.getActiveMesh()->getName(), Constants::KEYBOARD_KEY_DOWN)) {
                meshManager.setMovement(getMovementDistanceByName(meshManager.getActiveMesh()->getName()), -1.0);
            }
            break;

        case Constants::KEYBOARD_KEY_LEFT:
            if (canAutoMoveHorizotally(meshManager.getActiveMesh()->getName()) &&
                gameLogic.moveAuto(meshManager.getActiveMesh()->getName(), Constants::KEYBOARD_KEY_LEFT)) {
                meshManager.setMovement(getMovementDistanceByName(meshManager.getActiveMesh()->getName()), 1.0);
            }
            break;

        case Constants::KEYBOARD_KEY_RIGHT:
            if (canAutoMoveHorizotally(meshManager.getActiveMesh()->getName()) &&
                gameLogic.moveAuto(meshManager.getActiveMesh()->getName(), Constants::KEYBOARD_KEY_RIGHT)) {
                meshManager.setMovement(getMovementDistanceByName(meshManager.getActiveMesh()->getName()), -1.0);
            }
            break;
        }
    }
}

void setDynamicLight() {
    bool find = false;
    Node* light = Engine::getInstance().getList().getNode(0);
    for (int i = 1; i < Engine::getInstance().getList().size(); i++) {
        if (light->getType() == "PointLight") {
            find = true;
            break;
        }
        else light = Engine::getInstance().getList().getNode(i);
    }
    if (find) dynLight = dynamic_cast<PointLight*>(light);
}


void setLevel(int level) {
    Light::resetTotLights();
    Engine& engine = Engine::getInstance();
    engine.setTexturePath("../FileOvo/");
    if (level == 1) engine.load("../FileOvo", "Livello_1.ovo");
    if (level == 2) engine.load("../FileOvo", "Livello_2.ovo");
    if (level == 3) engine.load("../FileOvo", "Livello_3.ovo");
    gameLogic = GameLogic{level};
    gameEnded = false;
    setDynamicLight();
    engine.switchGameEnd(false);
}

void methodKeyboardCallback(unsigned char key, int mouseX, int mouseY) {
    const float dynamicLightMovementSpeed = 1.0f;
    Engine& eng = Engine::getInstance();
    Camera& camera = eng.getCamera();
    camera.setSpeedMovement(1.0);

    switch (key) {
    case '+': camera.moveUp(); break;
    case '-': camera.moveDown(); break;
    case 'a': camera.moveLeft(); break;
    case 'd': camera.moveRight(); break;
    case 's': camera.moveBackwards(); break;
    case 'w': camera.moveForward(); break;
    case 'x': camera.switchCamera(); break;
    case '2': camera.lookDown(); break;
    case '8': camera.lookUp(); break;
    case '4': camera.lookLeft(); break;
    case '6': camera.lookRight(); break;
    case '7': camera.rotateLeft(); break;
    case '9': camera.rotateRight(); break;
    case 'u': setLevel(1); break;
    case 'i': setLevel(2); break;
    case 'o': setLevel(3); break;
    case 'j': dynLight->translate(glm::vec3(dynamicLightMovementSpeed, 0.0, 0.0)); break;
    case 'g': dynLight->translate(glm::vec3(-dynamicLightMovementSpeed, 0.0, 0.0)); break;
    case 'z': dynLight->translate(glm::vec3(0.0, dynamicLightMovementSpeed, 0.0)); break;
    case 'h': dynLight->translate(glm::vec3(0.0, -dynamicLightMovementSpeed, 0.0)); break;
    case ',': dynLight->translate(glm::vec3(0.0, 0.0, -dynamicLightMovementSpeed)); break;
    case '.': dynLight->translate(glm::vec3(0.0, 0.0, dynamicLightMovementSpeed)); break;
    case '0': camera.setInitialPosition(); break;
    case 'q': eng.stop();
    default: break;
    }
}


void methodMouseCallback(int button, int state, int mouseX, int mouseY) {
    Engine& eng = Engine::getInstance();
    MeshMovementManager& meshManager = eng.getMeshManager();

    if (button == Constants::MOUSE_LEFT_BUTTON && state == Constants::MOUSE_DOWN && !meshManager.isMoving()) {
        Engine& eng = Engine::getInstance();

        Mesh::renderColorsOnly = true;
        eng.getList().rendering(Engine::getInstance().getCamera().getCameraInverse());

        Node* foundNode = eng.getNodeOnClick(mouseX, mouseY);
        Mesh* mesh = dynamic_cast<Mesh*>(foundNode);
        if (mesh && isAuto(mesh->getName())) {
            meshManager.setActiveMesh(mesh);
        }
        Mesh::renderColorsOnly = false;
    }
}

int main(int argc, char* argv[]) {
    Engine& eng = Engine::getInstance();
    eng.init(argc, argv, "RushHour", 100, 100);
    setLevel(1);
    eng.setTexturePath("../FileOvo/");

    eng.setBackgroundColor(0.0f, 0.0f, 0.0f);
    eng.timerCallback();
    eng.displayCallback();
    eng.reshapeCallback();
    eng.specialCallback(methodSpecialCallback);
    eng.keyboardCallback(methodKeyboardCallback);
    eng.mouseCallback(methodMouseCallback);
    while (eng.isRunning()) {
        eng.glutMainLoop();
    }
    eng.free();
    return 0;
}
