/**
 * @file List.h
 * @brief Definizione della classe List.
 *
 * Questo file contiene la definizione della classe List, che rappresenta una lista di nodi in una scena 3D.
 */

#ifndef LIST_HEADER
#define LIST_HEADER

#include "EngineExport.h"
#include "Node.h"

#include <list>
#include <glm/matrix.hpp>

 /**
  * @class List
  * @brief Rappresenta una lista di nodi in una scena 3D.
  *
  * La classe List è una classe che rappresenta una lista di nodi in una scena 3D.
  * Deriva dalla classe Object e fornisce funzionalità per la gestione di una collezione di nodi.
  */
class LIB_API List : public Object {
private:
    std::list<Node*> m_instances{}; ///< Lista di nodi.

public:
    /**
     * @brief Costruttore di default della classe List.
     */
	List() = default;

    /**
     * @brief Distruttore della classe List.
     */
    ~List() {}

    /**
     * @brief Aggiunge un nodo alla lista.
     * @param root Il nodo da aggiungere.
     */
    void addNode(Node* root);

    /**
     * @brief Funzione di rendering per la lista di nodi.
     * @param camera La matrice di vista.
     */
    void rendering(const glm::mat4& camera) const override;

    /**
     * @brief Rimuove tutti i nodi dalla lista.
     */
    void clear();

    /**
     * @brief Restituisce il nodo all'indice specificato nella lista.
     * @param idx L'indice del nodo da restituire.
     * @return Il nodo all'indice specificato.
     */
    Node* getNode(std::size_t idx) const;

    /**
     * @brief Restituisce la dimensione della lista (numero di nodi).
     * @return La dimensione della lista.
     */
    std::size_t size() const;
 
    /**
     * @brief Restituisce il nodo con l'ID specificato.
     * @param ID L'ID del nodo da cercare.
     * @return Il nodo con l'ID specificato o nullptr se non trovato.
     */
    Node* findById(std::size_t ID) const;
};

#endif


