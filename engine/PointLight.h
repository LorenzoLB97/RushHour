/**
 * @file PointLight.h
 * @brief Definizione della classe PointLight.
 *
 * Questo file contiene la definizione della classe PointLight, che rappresenta una sorgente di luce puntiforme nel sistema.
 */

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "EngineExport.h" 
#include "Light.h"

 /**
  * @class PointLight
  * @brief Rappresenta una sorgente di luce puntiforme nel sistema.
  *
  * La classe PointLight estende la classe base Light e rappresenta una sorgente di luce puntiforme all'interno del sistema.
  * La luce punta in tutte le direzioni da una posizione specifica.
  */
class LIB_API PointLight : public Light {
private:
    glm::vec3 position{}; ///< Posizione della sorgente di luce puntiforme.
    constexpr inline static float cutoff = 180.0f; ///< Angolo di taglio della luce.

public:
    /**
     * @brief Costruttore della classe PointLight.
     * @param type Il tipo della sorgente di luce.
     */
    PointLight(const std::string& type);

    /**
     * @brief Restituisce la posizione della sorgente di luce puntiforme.
     * @return La posizione della sorgente di luce puntiforme.
     */
    glm::vec3 getPosition() const;

    /**
     * @brief Imposta la posizione della sorgente di luce puntiforme.
     * @param position La nuova posizione della sorgente di luce puntiforme.
     */
    void setPosition(glm::vec3 position);

    /**
     * @brief Funzione di rendering per la sorgente di luce puntiforme.
     * @param inverse_camera La matrice di vista invertita.
     */
    void rendering(const glm::mat4& inverse_camera) const override;
};

#endif