/**
 * @file OvoParser.h
 * @brief Definizione della classe OvoParser
 *
 * Questo file contiene la definizione della classe OvoParser, principalmente utilizzata per fare il parsing di file .OVO.
 */

#ifndef OVOPARSER_HEADER
#define OVOPARSER_HEADER

#include <string>
#include <vector>
#include <optional>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <memory> // unique_ptr

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/packing.hpp>

#include "EngineExport.h" 
#include "Mesh.h"
#include "Material.h"
#include "Node.h"
#include "Light.h"
#include "SpotLight.h"
#include "Enums.h"
#include "Texture.h"



/**
 * @brief La classe OvoLoader gestisce il parsing dei file .ovo, estraendo e gestendo i dati della scena 3D.
 *
 * La classe OvoLoader si occupa del parsing dei file .ovo, che contengono informazioni sulle scene 3D,
 * inclusi materiali, texture e la struttura gerarchica della scena. Fornisce metodi per il caricamento,
 * l'elaborazione e l'accesso ai dati analizzati.
 *
 * @note Attualmente, non tutte le informazioni nel file .ovo vengono analizzate o utilizzate; alcuni dati vengono ignorati e non elaborati.
 *
 * @details La classe include funzionalità per il parsing di materiali, texture, nodi, mesh, mesh con ossatura, ossa
 * e proprietà fisiche. Costruisce una gerarchia di scene rappresentata dalla classe Node, con materiali e texture
 * gestiti tramite puntatori condivisi. La scena analizzata può essere accessa attraverso il nodo radice.
 *
 * Esempio di utilizzo:
 * ```cpp
 * OvoLoader loader;
 * loader.loadOvoFile("esempio.ovo");
 * std::unique_ptr<Node> radiceScena = std::move(loader.getRootNode()); // Nota: acquisisce la proprietà del nodo radice
 * ```
 *
 * @note La classe non è ancora completamente implementata, e alcuni dati potrebbero non essere elaborati nella versione attuale.
 * Aggiornamenti futuri potrebbero estendere la funzionalità per gestire ulteriori caratteristiche presenti nel formato del file .ovo.
 */
class LIB_API OvoParser {
private:
	/** Percorso della directory per i dati caricati. */
	std::filesystem::path m_directory;

	/** Collezione di puntatori a Material. */
	std::vector<std::shared_ptr<Material>> m_materials;

	/** Collezione di puntatori a Texture. */
	std::vector<std::shared_ptr<Texture>> m_textures;

	/** Puntatore unico a Node rappresentante la radice della scena. */
	std::unique_ptr<Node> m_root;

public:
	/**
	 * @brief Costruisce un oggetto OvoParser con la directory specificata.
	 * @param directory Il percorso alla directory contenente i file OVO.
	 */
	OvoParser(const std::filesystem::path& directory) : m_directory{ directory }
	{
	}

	/**
	 * @brief Analizza un file .ovo specifico e costruisce il grafico di scena.
	 * @param fileName Il nome del file .ovo da analizzare, cercato nella directory specificata nel costruttore.
	 * @details La funzione analizza prima tutto ciò che non è incluso nel grafico di scena (come i materiali),
	 * per poi procedere a costruire la scena del grafo basandosi sulle informazioni trovate.
	 */
	void parseFile(const std::string& fileName);

	/**
	 * @brief Ottiene il nodo radice della gerarchia della scena analizzata.
	 * @return Puntatore unico all'oggetto Node radice: la risorsa deve essere spostata (con std::move)
	 * se si desidera acquisire la proprietà del std::unique_ptr.
	 */
	std::unique_ptr<Node> getRoot();


	/**
	 * @brief Ottiene la collezione di materiali analizzati.
	 * @return Vettore (std::vector) di std::shared_ptr a oggetti Material.
	 */
	std::vector<std::shared_ptr<Material>> getMaterials() const;

	/**
	 * @brief Ottiene la collezione di texture analizzate.
	 * @return Vettore (std::vector) di std::shared_ptr a oggetti Texture.
	 */
	std::vector<std::shared_ptr<Texture>> getTextures() const;

private:
	/**
	 * @brief Analizza un nodo dal buffer fornito.
	 *
	 * Questo metodo estrae informazioni su un nodo, inclusi il suo nome, la matrice di trasformazione,
	 * il numero di figli e il nome di destinazione dal buffer fornito. Crea quindi un Nodo o un suo sotto tipo
	 * (ad esempio Node, Light, Mesh) con tutte le sue informazioni trovate nel file.
	 *
	 * @param buffer Il vettore di caratteri contenente i dati da analizzare.
	 * @param position La posizione all'interno del buffer. Aggiornata per riflettere i dati analizzati.
	 *
	 * @return Un std::unique_ptr al Node creato. Restituisce nullptr se la posizione è fuori limite o
	 *  se il tipo di oggetto nel buffer non è supportato.
	 */

	std::unique_ptr<Node> parseNode(const std::vector<char>& buffer, std::size_t& position);


	/**
	 * @brief Carica i contenuti del file specificato in memoria.
	 * @param file Lo stream di input del file.
	 * @return Vettore di caratteri contenente il contenuto del file.
	 */
	std::vector<char> loadFileIntoMemory(std::ifstream& file);

	/**
	 * @brief Analizza i chunk del file .ovo in base ai loro ID e dimensioni.
	 * @param chunkId L'ID del chunk da analizzare.
	 * @param chunkSize La dimensione del chunk da analizzare.
	 * @param input Lo stream di input del file.
	 */
	void dispatchChunkParsing(int chunkId, int chunkSize, std::ifstream& input);

	/**
	 * @brief Analizza l'header di un chunk e avanza la posizione.
	 * @param buffer Il buffer contenente l'intestazione del chunk.
	 * @param position La posizione corrente nel buffer.
	 * @return Coppia di ID del chunk e dimensione del chunk.
	 */
	std::pair<int, int> parseChunkHeader(const std::vector<char>& buffer, std::size_t& position);

	/**
	 * @brief Analizza le informazioni sulla versione del file OVO dal buffer.
	 * @param buffer Il vettore di caratteri contenente i dati da analizzare presi dal file OVO.
	 * @param position La posizione corrente all'interno del buffer.
	 */
	void parseVersion(const std::vector<char>& buffer, std::size_t& position);

	/**
	 * @brief Analizza le informazioni sul materiale dal buffer.
	 *
	 * Questo metodo estrae le informazioni sul materiale dal buffer riguardante il file, incluse il nome del materiale,
	 * i termini emissivi e albedo, la roughness, la metalness, l'alpha e le informazioni sulla texture associata.
	 * Viene creato un materiale condiviso, siccome più Mesh possono fare riferimento allo stesso Materiale.
	 *
	 * @param buffer Il vettore di caratteri contenente i dati da analizzare.
	 * @param position La posizione all'interno del buffer. Aggiornata per riflettere i dati analizzati.
	 */
	void parseMaterial(const std::vector<char>& buffer, std::size_t& position);


	/**
	 * @brief Analizza le informazioni sulla mesh dal buffer fornito e aggiorna l'oggetto Mesh specificato.
	 *
	 * Questo metodo estrae i dettagli su una mesh, come il suo sottotipo, il nome del materiale, il bounding box,
	 * le informazioni sul livello di dettaglio (LOD), i vertici e le facce dal buffer.
	 * Le informazioni analizzate vengono utilizzate per aggiornare l'oggetto Mesh fornito.
	 *
	 * @param buffer Il vettore di caratteri contenente i dati da analizzare.
	 * @param position La posizione all'interno del buffer. Aggiornata per riflettere i dati analizzati.
	 * @param isSkinned Un booleano che indica se la mesh è skinned.
	 * @param mesh Un puntatore all'oggetto Mesh da aggiornare con le informazioni analizzate.
	 * @note Nota che le Mesh skinned e le proprietà fisiche non vengono analizzate e vengono attualmente ignorate.
	 */
	void parseMesh(const std::vector<char>& buffer, std::size_t& position, bool isSkinned, Mesh* mesh);

	template<OvLightSubType lightType>
	void parseLight(const std::vector<char>& buffer, std::size_t& position, Light* light) {
		// Light color
		glm::vec3 color;
		std::memcpy(&color, buffer.data() + position, sizeof(glm::vec3));
		position += sizeof(glm::vec3);

		// Influence radius - Ignored
		//float radius;
		//std::memcpy(&radius, buffer.data() + position, sizeof(float));
		position += sizeof(float);

		// Direction
		glm::vec3 direction;
		std::memcpy(&direction, buffer.data() + position, sizeof(glm::vec3));
		position += sizeof(glm::vec3);

		// Cutoff (only for SpotLight). For PointLight, hardcoded to 180°
		float cutoff;
		std::memcpy(&cutoff, buffer.data() + position, sizeof(float));
		position += sizeof(float);

		float exponent;
		std::memcpy(&exponent, buffer.data() + position, sizeof(float));
		position += sizeof(float);

		if constexpr (lightType == OvLightSubType::SPOT) {
			SpotLight* spotLight = dynamic_cast<SpotLight*>(light);
			spotLight->setDirection(direction);
			spotLight->setLightCutoff(cutoff);
			spotLight->spotExponent(exponent);
		}

		// Ignored
		//bool castShadows;
		//std::memcpy(&castShadows, buffer.data() + position, sizeof(bool));
		position += sizeof(bool);

		// Ignored
		//bool isVolumetricLight;
		//std::memcpy(&isVolumetricLight, buffer.data() + position, sizeof(bool));
		position += sizeof(bool);

		// Set colors
		light->setLightAmbient(glm::vec4(glm::vec3(color.x), 1.0f));
		light->setLightDiffuse(glm::vec4(glm::vec3(color.y), 1.0f));
		light->setLightSpecular(glm::vec4(glm::vec3(color.z), 1.0f));
		light->setColor(color);
		light->enableLights();
	}

	/**
	 * @brief Analizza le informazioni sulle ossa dal buffer fornito.
	 *
	 * Questo metodo estrae dettagli su un osso, come il suo nome, la matrice, il numero di nodi figlio,
	 * il nome opzionale del target e il bounding box dal buffer. Le informazioni analizzate vengono utilizzate per
	 * aggiornare la rappresentazione interna delle ossa.
	 *
	 * @param buffer Il vettore di caratteri contenente i dati da analizzare.
	 * @param position La posizione all'interno del buffer. Aggiornata per riflettere i dati analizzati.
	 *
	 * @note Questa funzione attualmente incrementa solo la posizione fornita e ignora completamente le ossa nel file, senza analizzarle.
	 */
	void parseBones(const std::vector<char>& buffer, std::size_t& position);


	/**
	 * @brief Analizza le informazioni sulla mesh scheletrica dal buffer fornito.
	 *
	 * Questo metodo estrae dettagli su una mesh scheletrica, come la matrice di posizione,
	 * il numero di ossa, i nomi delle ossa, le matrici invertite delle ossa e i pesi delle ossa dal buffer.
	 *
	 * @param buffer Il vettore di caratteri contenente i dati da analizzare.
	 * @param position La posizione all'interno del buffer. Aggiornata per riflettere i dati analizzati.
	 * @param numOfVerticesPerLOD Numero di vertici per ogni livello di dettaglio (LOD).
	 *
	 * @note Attualmente questa funzione viene utilizzata solo per incrementare la posizione fornita. Non analizza nulla.
	 */
	void parseSkinnedMesh(const std::vector<char>& buffer, std::size_t& position, const std::vector<std::uint32_t>& numOfVerticesPerLOD);

	/**
	 * @brief Analizza le proprietà fisiche dal buffer fornito.
	 *
	 * Questa funzione estrae dettagli sulle proprietà fisiche, come tipo, impostazioni di collisione,
	 * massa, attrito, rimbalzo, smorzamento e informazioni personalizzate sull'involucro.
	 *
	 * @param buffer Il vettore di caratteri contenente i dati da analizzare.
	 * @param position La posizione all'interno del buffer. Aggiornata per riflettere i dati analizzati.
	 *
	 * @note Questa funzione è attualmente ignorata e non analizza alcun dato nel buffer.
	 */
	void parsePhysicsProperties(const std::vector<char>& buffer, std::size_t& position);

};

#endif