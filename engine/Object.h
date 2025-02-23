/**
 * @file Object.h
 * @brief Definizione della classe Object.
 *
 * Questo file contiene la definizione della classe Object, che rappresenta un oggetto di base all'interno del sistema.
 */

#ifndef OBJECT_HEADER
#define OBJECT_HEADER

#include <string>
#include <glm/matrix.hpp>

#include "EngineExport.h"

 /**
  * @class Object
  * @brief Rappresenta un oggetto di base all'interno del sistema.
  *
  * La classe Object fornisce funzionalità di base comuni a tutti gli oggetti nel sistema. Ogni oggetto ha un identificatore univoco,
  * un tipo e un nome associato. La classe è progettata per essere di base per altre classi più specializzate.
  */
class LIB_API Object {
private:
    static inline int idGenerator = 1; ///< Generatore di identificatori univoci.
    std::size_t m_id{}; ///< Identificatore univoco dell'oggetto.
    std::string m_type{}; ///< Tipo dell'oggetto.

protected:
    std::string m_objectName{}; ///< Nome dell'oggetto.

public:

    static void resetIdGenerator(){
        idGenerator = 1;
    }
    /**
     * @brief Costruttore di default della classe Object.
     */
    Object() = default;

    /**
     * @brief Costruttore della classe Object.
     * @param type Il tipo dell'oggetto.
     * @param name Il nome dell'oggetto.
     */
    Object(const std::string& type, const std::string& name);

    /**
     * @brief Distruttore virtuale della classe Object.
     */
    virtual ~Object() = default;

    /**
     * @brief Restituisce l'identificatore univoco dell'oggetto.
     * @return L'identificatore univoco dell'oggetto.
     */
    std::size_t getID() const;

    /**
    * @brief Restituisce il tipo dell'oggetto.
    * @return Il tipo dell'oggetto.
    */
    const std::string& getType() const;

    /**
     * @brief Restituisce il nome dell'oggetto.
     * @return Il nome dell'oggetto.
     */
    const std::string& getName() const;

    /**
     * @brief Imposta il tipo dell'oggetto.
     * @param type Il nuovo tipo dell'oggetto.
     */
    void setType(const std::string& type);

    /**
     * @brief Genera un colore univoco basato sull'identificatore univoco dell'oggetto.
     * @return Il colore univoco generato.
     */
    glm::vec4 generateUniqueColor() const;

    /**
     * @brief Funzione virtuale pura per il rendering dell'oggetto.
     * @param inverse_camera La matrice di vista invertita.
     */
    virtual void rendering(const glm::mat4& inverse_camera) const = 0;
};

#endif