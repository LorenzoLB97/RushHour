#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "EngineExport.h"
#include "Light.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @brief Rappresenta una luce direzionale in un ambiente grafico 3D.
 *
 * La classe rappresenta una luce direzionale utilizzata in un ambiente grafico 3D.
 * Estende la classe di base Light e aggiunge funzionalità specifiche per le luci direzionali.
 */
class LIB_API DirectionalLight : public Light {
private:
    glm::vec3 m_direction{}; ///< La direzione della luce direzionale.

public:
    /**
     * @brief Costruttore della classe DirectionalLight.
     * @param name Il nome della luce direzionale.
     */
    DirectionalLight(const std::string& name);

    /**
     * @brief Restituisce la direzione della luce direzionale.
     * @return La direzione della luce direzionale come vettore glm::vec3.
     */
    glm::vec3 getDirection() const;

    /**
     * @brief Imposta la direzione della luce direzionale.
     * @param direction La nuova direzione della luce direzionale.
     */
    void setDirection(glm::vec3 direction);

    /**
     * @brief Metodo per renderizzare la luce direzionale.
     * @param cameraInv La matrice di vista invertita.
     *
     * Questo metodo carica la matrice di modelview moltiplicata per la matrice di vista invertita
     * e imposta la posizione della luce direzionale. Poi chiama il metodo rendering della classe base Light.
     */
    void rendering(const glm::mat4& inverse_camera) const override;
};
#endif