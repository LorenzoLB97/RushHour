#ifndef SPOT_LIGHT
#define SPOT_LIGHT

#include "EngineExport.h" 
#include "Light.h"

/**
 * @brief Classe che rappresenta una luce spot nella scena.
 *
 * La classe SpotLight eredita dalla classe base Light e fornisce funzionalità specifiche per una luce spot,
 * inclusi metodi per impostare la direzione, l'angolo di taglio e l'esponente della luce spot. La luce spot
 * può essere resa nella scena utilizzando il metodo rendering.
 *
 * Esempio d'uso:
 * ```cpp
 * SpotLight mySpotLight("Spot1");
 * mySpotLight.setDirection(glm::vec3(1.0f, -1.0f, -1.0f));
 * mySpotLight.setLightCutoff(30.0f);
 * mySpotLight.spotExponent(50.0f);
 * ```
 *
 * @note La classe è parte di un sistema di illuminazione più grande e può essere utilizzata per rappresentare
 * una fonte di luce spot nella scena 3D.
 */
class LIB_API SpotLight : public Light {
private:
	glm::vec3 direction{ 1 };
	float cutOff{};
	float exponent{};

public:
	/**
	 * @brief Costruisce un oggetto SpotLight con il nome specificato.
	 *
	 * Questa classe rappresenta una luce spot nella scena. L'oggetto SpotLight è costruito con il nome specificato
	 * e deriva dalla classe base Light.
	 *
	 * @param name Il nome della SpotLight.
	 */
	SpotLight(const std::string& name);

	virtual ~SpotLight() {};


	/**
	 * @brief Esegue il rendering della luce spot nella scena.
	 *
	 * Questa funzione esegue il rendering della luce spot nella scena, utilizzando la matrice di vista inversa della camera.
	 * La direzione, l'angolo di taglio e l'esponente della luce spot vengono impostati e applicati durante il rendering.
	 *
	 * @param cameraInv La matrice di vista inversa della camera.
	 */
	void rendering(const glm::mat4& inverse_camera) const override;

	/**
	 * @brief Imposta la direzione della luce spot.
	 * @param lightDirection Il vettore di direzione della luce spot.
	 */
	void setDirection(const glm::vec3& lightDirection);


	/**
	 * @brief Imposta l'angolo di taglio della luce spot.
	 *
	 * @param lightCutoff L'angolo di taglio della luce spot.
	 */
	void setLightCutoff(float lightCutoff); 

	/**
	 * @brief Ottiene l'angolo di taglio della luce spot.
	 *
	 * @return L'angolo di taglio della luce spot.
	 */
	float getLightCutoff() const;

	/**
	 * @brief Ottiene la direzione della luce spot.
	 *
	 * @return La direzione della luce spot.
	 */
	glm::vec3 getDirection() const;


	/**
	 * @brief Ottiene l'esponente della luce spot.
	 *
	 * Questa funzione restituisce l'esponente della luce spot.
	 *
	 * @return L'esponente della luce spot.
	 */
	float getSpotExponent() const;

	/**
	 * @brief Imposta l'esponente della luce spot.
	 *
	 * @param exponent L'esponente della luce spot.
	 */
	void spotExponent(float exponent);
};

#endif 