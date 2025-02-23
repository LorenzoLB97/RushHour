/**
 * @file Texture.h.h
 * @brief Definizione della classe Texture.
 *
 * Questo file contiene la definizione della classe Texture utilizzata per rapprsentare le Texture nella scena.
 */

#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include "EngineExport.h" 
#include "Object.h"
#include <glm/fwd.hpp>

#define GL_TEXTURE_MAX_ANISOTROPY_EXT        0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT    0x84FF


/**
 * @brief Rappresenta una texture nella scena 3D.
 *
 * La classe Texture gestisce l'acquisizione, il caricamento e l'utilizzo di texture nei modelli 3D. Include
 * funzionalità per il rendering della texture, il recupero dell'ID della texture, e il settaggio e ottenimento
 * del percorso del file della texture. Inoltre, la classe offre il supporto per il filtraggio anisotropico quando
 * disponibile.
 *
 * Esempio d'uso:
 * ```cpp
 * Texture myTexture("Texture1");
 * myTexture.setPath("path/to/texture.png");
 * myTexture.setTextId();
 * myTexture.rendering(cameraInverseMatrix);
 * ```
 *
 * @note La classe supporta il caricamento di immagini di texture nei formati comuni e il rendering in un contesto
 * OpenGL.
 */
class LIB_API Texture : public Object {
private:
	static inline std::string path = "";
	bool isAnisotropicSupported = false;
	int anisotropicLevel = 1;
	bool bitmapExists = true;

	std::string textName{};
	unsigned int textId;

public:
	/**
	 * @brief Costruisce un oggetto Texture con il nome specificato.
	 *
	 * Questo costruttore inizializza un oggetto Texture con il nome fornito e imposta il tipo dell'oggetto su "Texture".
	 * Verifica anche il supporto per il filtraggio anisotropico e imposta i livelli anisotropici massimi se supportato.
	 *
	 * @param name Il nome della texture.
	 */
	Texture(const std::string name);

	~Texture();

	/**
	 * @brief Restituisce il percorso della directory delle texture.
	 *
	 * @return Il percorso della directory delle texture.
	 */
	std::string getPath();

	/**
	 * @brief Restituisce il livello anisotropico massimo supportato.
	 *
	 * @return Il livello anisotropico massimo supportato.
	 */
	bool getAnisotropicLevel();

	/**
	 * @brief Rendering della texture con le impostazioni specificate.
	 *
	 * Questa funzione imposta e applica le proprietà di rendering della texture, come le coordinate circolari,
	 * il filtraggio anisotropico, la filtrazione trilineare e il mappaggio mip.
	 *
	 * @param cameraInv La matrice di trasformazione inversa della camera.
	 */
	void rendering(const glm::mat4& cameraInv) const override;

	/**
	 * @brief Imposta l'ID della texture.
	 *
	 */
	void setTextId();

	/**
	 * @brief Imposta il percorso della directory delle texture.
	 *
	 * @param path Il percorso della directory delle texture.
	 */
	static void setPath(const std::string&);


	/**
	 * @brief Restituisce lo stato di esistenza del bitmap associato alla texture.
	 *
	 * @return True se il bitmap esiste, altrimenti False.
	 */
	bool checkBitmapExistence() const { return bitmapExists; }
};

#endif 