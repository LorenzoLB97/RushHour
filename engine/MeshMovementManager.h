/**
 * @file MeshMovementManager.h
 * @brief Definizione della classe MeshMovementManager.
 *
 * Questo file contiene la definizione della classe MeshMovementManager, che gestisce il movimento di una Mesh.
 */

#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include "Mesh.h"
#include "EngineExport.h"

 /**
  * @class MeshMovementManager
  * @brief Gestisce il movimento di una Mesh selezionata.
  *
  * La classe MeshMovementManager gestisce il movimento della Mesh attiva (selezionata), includendo blinking, velocità e altre configurazioni.
  */
class LIB_API MeshMovementManager {
private:
    Mesh* m_currentActiveMesh{}; ///< Puntatore alla mesh attiva.
    float m_blinking{}; ///< Fattore di lampeggiamento (blinking) per la mesh attiva.
    float m_limit{}; ///< Limite di movimento per la mesh attiva.
    float m_speed{}; ///< Velocità di movimento per la mesh attiva.
    bool m_isMoving{}; ///< Flag che indica se la mesh attiva è in movimento.

public:
    /**
     * @brief Imposta la mesh attiva.
     * @param mesh La mesh da impostare come attiva.
     */
    void setActiveMesh(Mesh* mesh);

  
    /**
     * @brief Imposta il movimento per la mesh attiva.
     * @param limit Il limite di movimento.
     * @param speed La velocità di movimento.
     */
    void setMovement(float limit, float speed = 1.0f);
    

    /**
     * @brief Verifica se la mesh attiva è in movimento.
     * @return True se la mesh attiva è in movimento, False altrimenti.
     */
    bool isMoving();

    /**
     * @brief Esegue l'effetto di lampeggiamento sulla mesh attiva.
     */
    void blink();

    /**
     * @brief Restituisce il limite di movimento per la mesh attiva.
     * @return Il limite di movimento.
     */
    float getLimit();

    /**
     * @brief Reimposta lo stato del MeshMovementManager.
     */
    void reset();

    /**
     * @brief Muove la mesh attiva durante la chiamata di display callback.
     */
    void moveActiveMesh();

    /**
     * @brief Restituisce la mesh attiva.
     * @return La mesh attiva.
     */
    Mesh* getActiveMesh();
};


#endif