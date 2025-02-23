#ifndef ENGINE_H
#define ENGINE_H

#include "EngineExport.h"
#include "List.h"
#include <memory> // shared_ptr
#include <vector>
#include "MeshMovementManager.h"
#include "PrimaryCamera.h" 

#define LIB_NAME      "Dynamic Library v.1" 
#define LIB_VERSION   10             


/**
 * @brief Rappresenta il motore grafico 3D.
 *
 * La classe Engine rappresenta un motore grafico 3D che gestisce la visualizzazione
 * e la manipolazione di oggetti 3D in una scena virtuale.
 */
class LIB_API Engine {
private:
    List m_list{};
    std::unique_ptr<Node> m_root{}; // Engine owns the root
    std::vector<std::shared_ptr<Material>> m_materials{}; // And holds all the materials, even if no mesh exists
    std::vector<std::shared_ptr<Texture>> m_textures{}; // And holds all the textures, even if no material exists
    MeshMovementManager m_meshManager{};
    Camera m_camera{"Camera01" };
    bool m_isRunning = true;
    int m_height{};

public:
    /**
     * @brief Costruttore di default per la classe Engine.
     */
    Engine() = default;


    /**
     * @brief Restituisce un'istanza singleton del motore.
     * @return Un riferimento all'istanza singleton del motore.
     */
    static Engine& getInstance();

    /**
     * @brief Inizializza il motore grafico.
     * @param argc Numero di argomenti della riga di comando.
     * @param argv Array di argomenti della riga di comando.
     * @param windowTitle Titolo della finestra di visualizzazione.
     * @param width Larghezza della finestra.
     * @param height Altezza della finestra.
     */
    void init(int argc, char** argv, const char* windowTitle, int width, int height);
    
    /**
     * @brief Carica un file di scena.
     * @param fileDirectory La directory del file di scena.
     * @param fileName Il nome del file di scena.
     */
    void load(const std::string& fileDirectory, const std::string& fileName);

    /**
     * @brief Imposta il colore di sfondo della finestra.
     * @param r Componente rossa del colore.
     * @param g Componente verde del colore.
     * @param b Componente blu del colore.
     */
    void setBackgroundColor(float r, float g, float b);
    
    /**
     * @brief Funzione di callback per la visualizzazione.
     */
    void displayCallback();
    
    /**
     * @brief Funzione di callback per il ridimensionamento della finestra.
     */
    void reshapeCallback();
    
    /**
     * @brief Funzione di callback per tasti speciali.
     * @param fnct Il puntatore a una funzione di callback per tasti speciali.
     */
    void specialCallback(void(*fnct)(int, int, int));
    
    /**
     * @brief Funzione di callback per la tastiera.
     * @param fnct Il puntatore a una funzione di callback per la tastiera.
     */
    void keyboardCallback(void(*fnct)(unsigned char, int, int));
    
    /**
     * @brief Funzione di callback per il mouse.
     * @param fnct Il puntatore a una funzione di callback per il mouse.
     */
    void mouseCallback(void(*fnct)(int, int, int, int));
    
    /**
     * @brief Restituisce lo stato di esecuzione del motore.
     * @return True se il motore è in esecuzione, False altrimenti.
     */
    bool isRunning();
    
    /**
     * @brief Rilascia le risorse allocate dal motore.
     */
    void free();
    
    /**
     * @brief Interrompe l'esecuzione del motore.
     */
    void stop();
    
    /**
     * @brief Chiama gli eventi di glut.
     */
    void callGlutEvent();
    
    /**
     * @brief Funzione di callback per il timer.
     */
    void timerCallback();
    
    /**
     * @brief Funzione di callback per il loop principale di glut.
     */
    void glutMainLoop();

    /**
     * @brief Imposta il percorso delle texture.
     * @param path Il percorso delle texture.
     */
    void setTexturePath(const std::string& path);

    /**
     * @brief Restituisce la lista di oggetti del motore.
     * @return Una referenza alla lista di oggetti del motore.
     */
    List& getList();

    /**
     * @brief Restituisce l'altezza della finestra.
     * @return L'altezza della finestra.
     */
    int getHeight();

    /**
     * @brief Imposta l'altezza della finestra.
     * @param height La nuova altezza della finestra.
     */
    void setHeight(int height);

    /**
     * @brief Restituisce la fotocamera del motore.
     * @return Una referenza alla fotocamera del motore.
     */
    Camera& getCamera() { return m_camera; }

    /**
     * @brief Restituisce il gestore di mesh del motore.
     * @return Una referenza al gestore di mesh del motore.
     */
    MeshMovementManager& getMeshManager() { return m_meshManager; }
    
    /**
     * @brief Restituisce il nodo cliccato sulla finestra.
     * @param mouseX La coordinata X del mouse.
     * @param mouseY La coordinata Y del mouse.
     * @return Un puntatore al nodo cliccato sulla finestra.
     */
    Node* getNodeOnClick(int mouseX, int mouseY) const;

    /**
     * @brief Attiva o disattiva la fine del gioco.
     * @param flag True per attivare la fine del gioco, False altrimenti.
     */
    void switchGameEnd(bool);
};


/**
 * @brief Funzione di callback per il ridimensionamento della finestra.
 * @param width La nuova larghezza della finestra.
 * @param height La nuova altezza della finestra.
 */
void methodReshapeCallback(int width, int height);

/**
 * @brief Funzione di callback per la visualizzazione.
 */
void methodDisplayCallback();

/**
 * @brief Funzione di callback per tasti speciali.
 * @param key Il tasto speciale premuto.
 * @param mouseX La coordinata X del mouse al momento della pressione del tasto.
 * @param mouseY La coordinata Y del mouse al momento della pressione del tasto.
 */
void methodSpecialCallback(int key, int mouseX, int mouseY);

/**
 * @brief Funzione di callback per il timer.
 * @param value Il valore passato alla funzione timer.
 */
void methodTimerCallback(int value);

/**
 * @brief Funzione di callback per la tastiera.
 * @param key Il tasto premuto.
 * @param mouseX La coordinata X del mouse al momento della pressione del tasto.
 * @param mouseY La coordinata Y del mouse al momento della pressione del tasto.
 */
void methodKeyboardCallback(unsigned char key, int mouseX, int mouseY);

/**
 * @brief Funzione di callback per il mouse.
 * @param button Il pulsante del mouse.
 * @param state Lo stato del pulsante del mouse.
 * @param mouseX La coordinata X del mouse al momento dell'evento.
 * @param mouseY La coordinata Y del mouse al momento dell'evento.
 */
void methodMouseCallback(int button, int state, int mouseX, int mouseY);


#endif