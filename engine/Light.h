/**
 * @file Light.h
 * @brief Definizione della classe Light.
 *
 * Questo file contiene la definizione della classe Light, che rappresenta una luce in una scena 3D.
 */

#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Node.h"
#include <string>
#include <cstddef> // std::size_t

 /**
  * @class Light
  * @brief Rappresenta una luce in una scena 3D.
  *
  * La classe Light è una classe di base per le luci in una scena 3D. Deriva dalla classe Node
  * e fornisce funzionalità di gestione delle luci come ambient, diffuse e specular lighting.
  */
class LIB_API Light : public Node {
protected:
    glm::vec3 m_transPosition{}; ///< Posizione trasformata della luce.
    glm::mat4 m_transLight{}; ///< Trasformazione della luce.
    glm::vec4 m_lightAmbient{}; ///< Colore ambient della luce.
    glm::vec4 m_lightDiffuse{}; ///< Colore diffuse della luce.
    glm::vec4 m_lightSpecular{}; ///< Colore specular della luce.
    glm::vec3 m_lightColor{}; ///< Colore della luce come vettore glm::vec3.
    std::size_t m_lightNum{}; ///< Numero univoco assegnato alla luce.
    static inline std::size_t totLights = 0; ///< Totale delle luci create.

public:
    /**
     * @brief Costruttore della classe Light.
     * @param type Tipo della luce.
     * @param name Nome della luce.
     */
    Light(const std::string& type, const std::string& name);

    /**
     * @brief Distruttore della classe Light.
     */
    ~Light();

    /**
     * @brief Abilita le luci.
     */
    void enableLights();

    /**
     * @brief Funzione di rendering della luce.
     * @param cameraInv Matrice di vista invertita.
     */
    void rendering(const glm::mat4& cameraInv) const override;
      
    /**
     * @brief Imposta il colore ambient della luce.
     * @param lightAmbient Il nuovo colore ambient della luce.
     */
    void setLightAmbient(glm::vec4 lightAmbient); 
    
    /**
 * @brief Imposta il colore diffuse della luce.
 * @param lightDiffuse Il nuovo colore diffuse della luce.
 */
    void setLightDiffuse(glm::vec4 lightDiffuse); 
    
    /**
     * @brief Imposta il colore specular della luce.
     * @param lightSpecular Il nuovo colore specular della luce.
     */
    void setLightSpecular(glm::vec4 lightSpecular); 
    
    /**
     * @brief Imposta il colore della luce.
     * @param color Il nuovo colore della luce come vettore glm::vec3.
     */
    void setColor(const glm::vec3& color);

    /**
     * @brief Restituisce il numero univoco della luce.
     * @return Il numero univoco della luce.
     */
    std::size_t getLightNumber() const;

    /**
     * @brief Resetta il totale delle luci create.
     */
    static void resetTotLights() {
        totLights = 0;
    }
};

#endif