
// GLM:   
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

// GLEW:
#include <gl/glew.h>

// FreeGLUT:   
#include <GL/freeglut.h>

// C/C++:
#include "PrimaryCamera.h" 
#include "engine.h"
#include "Node.h"
#include "Light.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "OvoParser.h"

#include <cstdio>
#include <FreeImage.h>

/////////////
// GLOBALS //
/////////////
int windowId{};
int frames{};
int fps{};

bool gameEnd = false;

void Engine::switchGameEnd(bool b) {
    gameEnd = b;
}

void Engine::glutMainLoop() {
    glutMainLoopEvent();
}

bool Engine::isRunning() {
    return m_isRunning;
}

void Engine::free() {
    FreeImage_DeInitialise();
    // Rest: deallocated implicitly (smart pointers)
}

void Engine::stop() {
    m_isRunning = false;
}

Engine& Engine::getInstance() {
    static Engine instance;
    return instance;
}

void Engine::init(int argc, char** argv, const char* windowTitle, int width, int height) {
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(width, height);
    glutInitWindowSize(900, 600);
    FreeImage_Initialise();

    windowId = glutCreateWindow(windowTitle);

    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glEnable(GL_NORMALIZE);  
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0f); // default 0
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Engine::load(const std::string& fileDirectory, const std::string& fileName) {
    static std::size_t idx = 1;
    OvoParser ovoParser(fileDirectory);
    ovoParser.parseFile(fileName);

    m_root = std::move(ovoParser.getRoot());
    m_materials = ovoParser.getMaterials();
    m_textures = ovoParser.getTextures();
    Object::resetIdGenerator();
    Light::resetTotLights();
    m_meshManager.reset();
    m_list.clear();
    m_list.addNode(m_root.get());
}

void displayText(const char* text, int xPosition, int yPosition, void* font) {
    glDisable(GL_LIGHTING);

    // white color
    glColor3f(1.0f, 1.0f, 1.0f);

    // settare la posizione
    glRasterPos2f(static_cast<GLfloat>(xPosition), static_cast<GLfloat>(yPosition));

    // mostrare il testo
    glutBitmapString(font, reinterpret_cast<const unsigned char*>(text));

    glEnable(GL_LIGHTING);
}

void methodDisplayCallback() {
    Engine& eng = Engine::getInstance();
    Camera& camera = eng.getCamera();
    MeshMovementManager& meshManager = eng.getMeshManager();

    camera.to3dMode();
    meshManager.moveActiveMesh();
    Engine::getInstance().getList().rendering(camera.getCameraInverse());
    meshManager.blink();

    // Switch to 2d to print text
    camera.to2dMode();

    // Calcola la larghezza del testo
    const std::string fpsText = "FPS: " + std::to_string(fps);
    int textWidth = glutBitmapLength(GLUT_BITMAP_8_BY_13, (unsigned char*)fpsText.c_str());

    // Posiziona il testo nell'angolo in alto a destra
    int xPosition = glutGet(GLUT_WINDOW_WIDTH) - textWidth - 10; // 10 è una piccola spaziatura dal bordo
    int yPosition = glutGet(GLUT_WINDOW_HEIGHT) - 15; // 15 è una piccola spaziatura dal bordo
    displayText(fpsText.c_str(), xPosition, yPosition, GLUT_BITMAP_8_BY_13);

    // Display camera commands text
    const  std::string commandsText = "Camera commands: \n w-a-s-d to your view up,"
        "left, down, right \n + -to move up and down \n 8 - 2 to look up and down \n 4 - 6 to look right and left"
        "\n 7 - 9 to rotate yourself \n u - i - o to switch levels \n q to quit";
    displayText(commandsText.c_str(), 5, 105, GLUT_BITMAP_8_BY_13);

    if (gameEnd) {
        const std::string victoryText = "HAI VINTO!";
        const int victoryTextWidth = glutBitmapLength(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)victoryText.c_str());
        const int xVictoryPosition = (glutGet(GLUT_WINDOW_WIDTH) / 2) - (victoryTextWidth / 2);
        const int yVictoryPosition = glutGet(GLUT_WINDOW_HEIGHT) / 2;

        displayText(victoryText.c_str(), xVictoryPosition, yVictoryPosition, GLUT_BITMAP_TIMES_ROMAN_24);
    }

    // switch back to 3d mode
    camera.to3dMode();

    frames++;
    // Swap this context's buffer:     
    glutSwapBuffers();
    glutPostWindowRedisplay(windowId);
}

void methodReshapeCallback(int width, int height) {
    Engine& engine = Engine::getInstance();
    Camera& camera = engine.getCamera();
    glViewport(0, 0, width, height);

    camera.setProjectionMatrix(static_cast<float>(width), static_cast<float>(height));
    camera.setOrthogonalMatrix(glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f));
    engine.setHeight(height);
}

Node* Engine::getNodeOnClick(int mouseX, int mouseY) const {
    GLubyte pixel[4];
    glReadPixels(mouseX, m_height - mouseY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    const int objId = static_cast<int>(pixel[0]);
    return Engine::getInstance().getList().findById(objId);
}

/**
 * This callback is invoked each 3 seconds.
 * @param value passepartout value
 */
void methodTimerCallback(int value)
{
    fps = static_cast<int>(frames / 1.0f);
    frames = 0;

    // Register the next update:
    glutTimerFunc(1000, methodTimerCallback, 0);
}

int Engine::getHeight() {
    return m_height;
}

void Engine::setHeight(int height) {
    m_height = height;
}

void Engine::reshapeCallback()
{
    glutReshapeFunc(methodReshapeCallback);
}

void Engine::timerCallback() {
    glutTimerFunc(1000, methodTimerCallback, 0);
}

void Engine::specialCallback(void(*fnct)(int, int, int)) {
    glutSpecialFunc(fnct);
}

void Engine::displayCallback() {
    glutDisplayFunc(methodDisplayCallback);

}

void Engine::keyboardCallback(void(*fnct)(unsigned char, int, int)) {
    glutKeyboardFunc(fnct);
}

void Engine::mouseCallback(void(*fnct)(int, int, int, int)) {
    glutMouseFunc(fnct);
}


void Engine::callGlutEvent() {
    glutMainLoopEvent();
}

void Engine::setBackgroundColor(float r, float g, float b) {
    glClearColor(r, g, b, 1.0f);
}

List& Engine::getList() {
    return m_list;
}

void Engine::setTexturePath(const std::string& path) {
    Texture::setPath(path);
}