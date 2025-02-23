/**
 * @file Node.h
 * @brief Definizione della classe Node.
 *
 * Questo file contiene la definizione della classe Node, che rappresenta un nodo nella gerarchia di una scena 3D.
 */

#ifndef NODE_HEADER_H
#define NODE_HEADER_H

#include "EngineExport.h"
#include "Object.h"

#include <vector>
#include <memory>
#include <glm/glm.hpp>

 /**
  * @class Node
  * @brief Rappresenta un nodo nella gerarchia di una scena 3D.
  *
  * La classe Node rappresenta un nodo nella gerarchia di una scena 3D.
  */
class LIB_API Node : public Object {
protected:
	glm::mat4 m_localMatrix{};  ///< Matrice di trasformazione locale.
	glm::mat4 m_globalMatrix{}; ///< Matrice globale nel mondo.
	Node* m_parent{}; ///< Puntatore al nodo genitore.
	std::vector<std::unique_ptr<Node>> m_children{}; ///< Vettore di nodi figli.

public:
	/**
	 * @brief Costruttore della classe Node.
	 * @param type Il tipo del nodo.
	 * @param name Il nome del nodo.
	 */
	Node(const std::string& type, const std::string& name);
	
	/**
	 * @brief Distruttore virtuale della classe Node.
	 */
	virtual ~Node() = default;
	
	/**
	 * @brief Imposta la matrice di trasformazione locale.
	 * @param matrix La matrice di trasformazione locale.
	 */
	void set_local_matrix(const glm::mat4& matrix);
	
	/**
	 * @brief Aggiunge un nodo figlio.
	 * @param child Il nodo figlio da aggiungere.
	 */
	void add_child(std::unique_ptr<Node> child);
	
	/**
	 * @brief Trasla il nodo.
	 * @param translation Il vettore di traslazione.
	 */
	void translate(const glm::vec3& translation);
	
	/**
	 * @brief Trova un nodo per ID.
	 * @param id L'ID del nodo da trovare.
	 * @return Puntatore al nodo trovato o nullptr se non trovato.
	 */
	Node* findNodeById(std::size_t id);
	
	/**
	 * @brief Aggiorna le matrici globali.
	 */
	void updateGlobalMatrices(); 

	/**
	 * @brief Restituisce la matrice di trasformazione locale.
	 * @return La matrice di trasformazione locale.
	 */
	glm::mat4 get_local_matrix() const;
	
	/**
	 * @brief Restituisce il nodo figlio all'indice specificato.
	 * @param idx L'indice del nodo figlio.
	 * @return Puntatore al nodo figlio.
	 */
	Node* getAt(std::size_t idx);
	
	/**
	 * @brief Restituisce il nodo genitore.
	 * @return Puntatore al nodo genitore.
	 */
	Node* get_parent() const;
	
	/**
	 * @brief Restituisce il numero di nodi figli.
	 * @return Il numero di nodi figli.
	 */
	std::size_t get_children_num() const;
	
	/**
	 * @brief Restituisce la matrice finale nel mondo.
	 * @return La matrice finale nel mondo.
	 */
	glm::mat4 getFinalMatrix() const;

	/**
	 * @brief Funzione di rendering del nodo.
	 * @param inverse_camera La matrice di vista invertita.
	 */
	void rendering(const glm::mat4& inverse_camera) const override;


	/**
	 * @nota Necessario eliminare la copia e l'assegnazione di copia a causa di unique_ptr e dllexport. Vedere: https://stackoverflow.com/questions/51033325/dll-exporting-causing-issues-with-unique-pointers
	 */
	Node(const Node&) = delete;
	Node& operator=(const Node&) = delete;
};

#endif
