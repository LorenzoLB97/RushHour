/**
 * @file Material.h
 * @brief Definizione della classe Material.
 *
 * Questo file contiene la definizione della classe Material, che rappresenta un materiale in una scena 3D.
 */

#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER 

#include "EngineExport.h"
#include "Object.h"
#include "Texture.h" 

#include <memory> //shared_ptr

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/fwd.hpp>


 /**
  * @struct MaterialSettings
  * @brief Struttura che contiene le impostazioni del materiale.
  *
  * La struttura MaterialSettings contiene informazioni sul colore, sull'emissione e sulle caratteristiche
  * del materiale come ambient, diffuse e specular. Include anche la brillantezza (shininess) e l'alpha.
  */
struct LIB_API MaterialSettings {
    glm::vec4 emission = glm::vec4(0.0f); ///< Colore di emissione del materiale.
    glm::vec4 emissionBackup = glm::vec4(0.0f); ///< Backup del colore di emissione del materiale.
    glm::vec4 ambient = glm::vec4(0.0f); ///< Colore ambient del materiale.
    glm::vec4 diffuse = glm::vec4(0.0f); ///< Colore diffuse del materiale.
    glm::vec4 specular = glm::vec4(0.0f); ///< Colore specular del materiale.
    float shininess = 0.0f; ///< Brillantezza del materiale.
    float alpha = 1.0f; ///< Valore alpha del materiale.
};

/**
 * @class Material
 * @brief Rappresenta un materiale in una scena 3D.
 *
 * La classe Material rappresenta un materiale utilizzato per la resa di oggetti in una scena 3D.
 * Deriva dalla classe Object e fornisce funzionalità per la gestione delle impostazioni del materiale e delle texture.
 */
class LIB_API Material : public Object {
private:
    MaterialSettings m_materialSettings{}; ///< Impostazioni del materiale.
    std::shared_ptr<Texture> m_texture{}; ///< Puntatore condiviso alla texture associata al materiale.


public:
    /**
     * @brief Costruttore della classe Material.
     * @param name Il nome del materiale.
     */
    Material(const std::string& name);

    /**
     * @brief Costruttore di default della classe Material.
     */
    Material() = default;

    /**
     * @brief Distruttore della classe Material.
     */
    ~Material() {}

    /**
     * @brief Modifica l'emissione del materiale in modo intermittente (effetto lampeggiante).
     * @param blinking Il fattore di lampeggiamento.
     */
    void blinkEmission(float blinking);

    /**
     * @brief Imposta il backup del colore di emissione del materiale.
     */
    void setEmissionBackup();

    /**
     * @brief Ripristina il colore di emissione del materiale dal backup.
     */
    void resetEmissionFromBackup();

    /**
     * @brief Imposta la texture associata al materiale.
     * @param texture La texture da associare.
     */
    void setTexture(const std::shared_ptr<Texture>& texture);
    
    /**
     * @brief Imposta le impostazioni del materiale.
     * @param emission Il colore di emissione.
     * @param shininess La brillantezza del materiale.
     * @param ambient Il colore ambient.
     * @param diffuse Il colore diffuse.
     * @param specular Il colore specular.
     * @param alpha Il valore alpha del materiale.
     */
    void setMaterialSettings(const glm::vec4& emission, float shininess, const glm::vec4& ambient, 
        const glm::vec4& diffuse, const glm::vec4& specular, float alpha);

    /**
     * @brief Verifica se una texture è presente.
     * @return True se una texture è presente, False altrimenti.
     */
    bool isTexturePresent() const;

    /**
     * @brief Carica le impostazioni del materiale.
     */
    void loadMaterialSettings() const;

    /**
     * @brief Restituisce le impostazioni del materiale.
     * @return Le impostazioni del materiale.
     */
    MaterialSettings getMaterialSettings() const;

    /**
     * @brief Funzione di rendering del materiale.
     * @param inverse_camera La matrice di vista invertita.
     */
    void rendering(const glm::mat4& inverse_camera) const override;
};

#endif