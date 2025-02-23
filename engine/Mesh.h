/**
 * @file Mesh.h
 * @brief Definizione della classe Mesh.
 *
 * Questo file contiene la definizione della classe Mesh, che rappresenta una mesh in una scena 3D.
 */

#ifndef MESH_HEADER
#define MESH_HEADER

#include "EngineExport.h"
#include "Node.h"
#include "Material.h"
#include "MeshStructures.h"

#include <vector>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

 /**
  * @class Mesh
  * @brief Rappresenta una mesh in una scena 3D.
  *
  * La classe Mesh rappresenta una mesh utilizzata per la resa di oggetti in una scena 3D.
  * Deriva dalla classe Node e contiene informazioni sul materiale associato e dettagli di livello di dettaglio (LOD).
  */
class LIB_API Mesh : public Node {
private:
    std::shared_ptr<Material> m_material{}; ///< Materiale associato alla mesh.
    std::vector<LodData> m_LodInfo{}; ///< Informazioni sui livelli di dettaglio (LOD) della mesh.

public:
    static inline bool renderColorsOnly = false;

public:
    /**
     * @brief Costruttore della classe Mesh.
     * @param name Il nome della mesh.
     */
    Mesh(const std::string& name);

    /**
     * @brief Distruttore virtuale della classe Mesh.
     */
    virtual ~Mesh() = default;

    /**
     * @brief Imposta il materiale associato alla mesh.
     * @param material Il materiale da associare alla mesh.
     */
    void setMaterial(const std::shared_ptr<Material>& material);

    /**
     * @brief Imposta le informazioni sui livelli di dettaglio (LOD) della mesh.
     * @param lodInfo Le informazioni sui livelli di dettaglio.
     */
    void setLodInfo(const std::vector<LodData>& lodInfo);   

    /**
     * @brief Restituisce il materiale associato alla mesh.
     * @return Il materiale associato alla mesh.
     */
    Material* getMaterial() { return m_material.get(); }

    /**
     * @brief Funzione di rendering della mesh.
     * @param inverse_camera La matrice di vista invertita.
     */
    void rendering(const glm::mat4& inverse_camera) const override;

private:
    /**
     * @brief Renderizza la mesh.
     */
    void renderMesh() const;

    /**
     * @brief Renderizza la mesh per l'ombra.
     * @param camera La matrice di vista.
     */
    void renderShadowMesh(const glm::mat4& camera) const;
    
    /**
     * @brief Renderizza solo i colori della mesh.
     */
    void renderMeshColorOnly() const;
};

#endif