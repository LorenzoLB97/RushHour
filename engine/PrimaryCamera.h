/**
 * @file PrimaryCamera.h
 * @brief Definizione della classe Camera.
 *
 * Questo file contiene la definizione della classe Camera, che rappresenta una telecamera nel sistema.
 */

#ifndef PRIMARYCAMERA_H
#define PRIMARYCAMERA_H   

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EngineExport.h" 
#include "Node.h"

 /**
  * @class Camera
  * @brief Rappresenta una telecamera nel sistema.
  *
  * La classe Camera estende la classe Node e rappresenta una telecamera nel sistema. La telecamera può essere
  * configurata per il movimento dinamico o statico, con la possibilità di spostarsi e ruotare in uno spazio tridimensionale.
  */
class LIB_API Camera : public Node {
private:
    bool m_isDynamic = true; ///< Flag che indica se la telecamera è in modalità dinamica o statica.
    float m_speed{}; ///< Velocità di movimento della telecamera.
    float m_angleX{}; ///< Angolo di rotazione attorno all'asse X.
    float m_angleY{}; ///< Angolo di rotazione attorno all'asse Y.
    float m_angleZ{}; ///< Angolo di rotazione attorno all'asse Z.
    float m_distance{}; ///< Distanza della telecamera dall'oggetto di riferimento.
    float m_eyeX{}; ///< Coordinata X della posizione dell'occhio.
    float m_eyeY{}; ///< Coordinata Y della posizione dell'occhio.
    float m_eyeZ{}; ///< Coordinata Z della posizione dell'occhio.
    float m_atX{}; ///< Coordinata X del punto di vista.
    float m_atY{}; ///< Coordinata Y del punto di vista.
    float m_nearPlane = 1.0f; ///< Piano vicino della telecamera.
    float m_fov = 45.0f; ///< Campo visivo della telecamera.
    float m_farPlane = 1000.0f; ///< Piano lontano della telecamera.

    glm::mat4 m_orthoMatrix{}; ///< Matrice ortografica.
    glm::mat4 m_projMatrix{}; ///< Matrice di proiezione.
    glm::mat4 m_dynamicCameraLookAt{}; ///< Vista della telecamera dinamica.
    glm::mat4 m_dynamicCamera{}; ///< Telecamera dinamica.
    glm::mat4 m_staticCameraLookAt{}; ///< Vista della telecamera statica.
    glm::mat4 m_currentCamera{}; ///< Telecamera corrente.
    glm::mat4 m_staticCamera = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 254.0f, 63.0f)) * m_staticCameraLookAt; ///< Telecamera statica.

public:
    /**
     * @brief Costruttore della classe Camera.
     * @param name Il nome della telecamera.
     */
    Camera(const std::string& name);

    /**
     * @brief Imposta la posizione iniziale della telecamera.
     */
    void setInitialPosition();

    /**
     * @brief Imposta la velocità di movimento della telecamera.
     * @param speed La velocità di movimento desiderata.
     */
    void setSpeedMovement(float speed);

    /**
     * @brief Restituisce la matrice ortografica della telecamera.
     * @return La matrice ortografica della telecamera.
     */
    glm::mat4 getOrthogonalMatrix() const;

    /**
     * @brief Imposta la matrice ortografica della telecamera.
     * @param orthogonalMatrix La nuova matrice ortografica.
     */
    void setOrthogonalMatrix(const glm::mat4& orthogonalMatrix);

    /**
     * @brief Carica la matrice di proiezione della telecamera.
     */
    void loadProjectionMatrix();

    /**
     * @brief Abilita la modalità 3D della telecamera.
     */
    void to3dMode() const;

    /**
     * @brief Abilita la modalità 2D della telecamera.
     */
    void to2dMode() const;
    /**
      * @brief Sposta la telecamera in avanti.
      */
    void moveForward();

    /**
     * @brief Sposta la telecamera a sinistra.
     */
    void moveLeft();

    /**
     * @brief Sposta la telecamera a destra.
     */
    void moveRight();

    /**
     * @brief Sposta la telecamera indietro.
     */
    void moveBackwards();

    /**
     * @brief Sposta la telecamera verso l'alto.
     */
    void moveUp();

    /**
     * @brief Sposta la telecamera verso il basso.
     */
    void moveDown();

    /**
     * @brief Inclina la telecamera verso l'alto.
     */
    void lookUp();

    /**
     * @brief Inclina la telecamera verso il basso.
     */
    void lookDown();

    /**
     * @brief Inclina la telecamera a sinistra.
     */
    void lookLeft();

    /**
     * @brief Inclina la telecamera a destra.
     */
    void lookRight();

    /**
     * @brief Ruota la telecamera verso sinistra.
     */
    void rotateLeft();

    /**
     * @brief Ruota la telecamera verso destra.
     */
    void rotateRight();

    /**
     * @brief Imposta la matrice di proiezione della telecamera.
     * @param width La larghezza della finestra.
     * @param height L'altezza della finestra.
     * @return La matrice di proiezione della telecamera.
     */
    glm::mat4 setProjectionMatrix(float width, float height);

    /**
     * @brief Cambia la modalità della telecamera tra dinamica e statica.
     */
    void switchCamera();

    /**
     * @brief Restituisce la matrice inversa della telecamera.
     * @return La matrice inversa della telecamera.
     */
    glm::mat4 getCameraInverse() const;

    /**
     * @brief Ricarica la telecamera dinamica.
     */
    void reloadDynamicCamera();

    /**
     * @brief Verifica se la telecamera è in modalità dinamica.
     * @return True se la telecamera è in modalità dinamica, false altrimenti.
     */
    bool isDynamic();
    /**
     * @brief Restituisce la velocità di movimento della telecamera.
     * @return La velocità di movimento della telecamera.
     */
    float getSpeedMovement();

    /**
     * @brief Restituisce l'angolo X della telecamera.
     * @return L'angolo X della telecamera.
     */
    float getAngleX();

    /**
     * @brief Restituisce l'angolo Y della telecamera.
     * @return L'angolo Y della telecamera.
     */
    float getAngleY();

    /**
     * @brief Restituisce l'angolo Z della telecamera.
     * @return L'angolo Z della telecamera.
     */
    float getAngleZ();

    /**
     * @brief Restituisce la distanza della telecamera.
     * @return La distanza della telecamera.
     */
    float getDistance();

    /**
     * @brief Restituisce la coordinata X dell'occhio della telecamera.
     * @return La coordinata X dell'occhio della telecamera.
     */
    float getEyeX();

    /**
     * @brief Restituisce la coordinata Y dell'occhio della telecamera.
     * @return La coordinata Y dell'occhio della telecamera.
     */
    float getEyeY();

    /**
     * @brief Restituisce la coordinata Z dell'occhio della telecamera.
     * @return La coordinata Z dell'occhio della telecamera.
     */
    float getEyeZ();

    /**
     * @brief Restituisce la coordinata X del punto di visuale della telecamera.
     * @return La coordinata X del punto di visuale della telecamera.
     */
    float getAtX();

    /**
     * @brief Restituisce la coordinata Y del punto di visuale della telecamera.
     * @return La coordinata Y del punto di visuale della telecamera.
     */
    float getAtY();

    /**
     * @brief Restituisce la matrice di proiezione della telecamera.
     * @return La matrice di proiezione della telecamera.
     */
    glm::mat4 getProjectionMatrix();
    
};

#endif  