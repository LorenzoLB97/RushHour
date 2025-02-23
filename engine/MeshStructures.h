/**
 * @file MeshStructs.h
 * @brief Definizione delle strutture per i dati della mesh.
 *
 * Questo file contiene la definizione delle strutture VertexData e LodData utilizzate per rappresentare i dati della mesh.
 */

#ifndef MESH_STRUCTS_H
#define MESH_STRUCTS_H

#include "EngineExport.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <array>


 /**
  * @struct VertexData
  * @brief Rappresenta i dati di un singolo vertice della mesh.
  *
  * La struttura VertexData contiene le informazioni su posizione, normale, coordinate di texture e tangente di un vertice della mesh.
  */
struct LIB_API VertexData {
    glm::vec3 vertex; ///< Posizione del vertice.
    glm::vec4 normal; ///< Normale del vertice.
    glm::vec2 textureData; ///< Coordinate di texture del vertice.
    glm::vec4 tangentData; ///< Tangente del vertice.
};

/**
 * @struct LodData
 * @brief Rappresenta i dati di un livello di dettaglio (LOD) della mesh.
 *
 * La struttura LodData contiene il numero di vertici e facce, nonché i vettori di vertici e facce per un LOD della mesh.
 */
struct LIB_API LodData {
    std::int32_t numVertices; ///< Numero di vertici nel LOD.
    std::int32_t numFaces; ///< Numero di facce nel LOD.
    std::vector<VertexData> vertices; ///< Vettore di dati dei vertici.
    std::vector<std::array<std::uint32_t, 3>> faces; ///< Vettore di indici delle facce.
};

#endif