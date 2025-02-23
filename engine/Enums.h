#ifndef ENUMERATIVES_H
#define ENUMERATIVES_H

/**
 * @brief Enumerativo per i tipi di luci Ov.
 *
 * L'enumerativo OvLightSubType definisce i possibili tipi di luci Ov.
 * I valori possibili sono: OMNI, DIRECTIONAL, SPOT.
 */
enum class OvLightSubType : int {
    OMNI,          ///< Luce omni.
    DIRECTIONAL,   ///< Luce direzionale.
    SPOT,          ///< Luce spot.
    LAST           ///< Valore di marcatura finale.
};


/**
 * @brief Enumerativo per i tipi di mesh Ov.
 *
 * L'enumerativo OvMeshSubType definisce i possibili tipi di mesh Ov, come default, normal mapped e tessellated.
 * I valori possibili sono: DEFAULT, NORMALMAPPED, TESSELLATED.
 */
enum class OvMeshSubType : int {
    DEFAULT,       ///< Mesh di tipo predefinito.
    NORMALMAPPED,  ///< Mesh normal mappata.
    TESSELLATED,   ///< Mesh tessellata.
    LAST           ///< Valore di marcatura finale.
};


/**
 * @brief Enumerativo per i tipi di oggetti Ov.
 *
 * L'enumerativo OvObjectType definisce i possibili tipi di oggetti Ov, come nodo, mesh, luce, camera, ecc.
 * I valori possibili sono definiti dall'elenco di tipi presenti nell'enumerativo.
 */
enum class OvObjectType : int {
    OBJECT = 0,
    NODE,
    OBJECT2D,
    OBJECT3D,
    LIST,
    BUFFER,
    SHADER,
    TEXTURE,
    FILTER,
    MATERIAL,
    FBO,
    QUAD,
    BOX,
    SKYBOX,
    FONT,
    CAMERA,
    LIGHT,
    BONE,
    MESH,
    SKINNED,
    INSTANCED,
    PIPELINE,
    EMITTER,
    ANIM,
    PHYSICS,
    LAST           ///< Valore di marcatura finale.
};



#endif