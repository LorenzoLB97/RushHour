#include "../Node.h"
#include <cassert>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void testNodeMethods() {
    // Creazione di un nodo radice
    Node rootNode("RootType", "RootNode");

    // Verifica dell'ID, del tipo e del nome
    assert(rootNode.getID() == 6);
    assert(rootNode.getType() == "RootType");
    assert(rootNode.getName() == "RootNode");

    // Aggiunta di un nodo figlio
    std::unique_ptr<Node> childNode = std::make_unique<Node>("ChildType", "ChildNode");
    rootNode.add_child(std::move(childNode));

    // Verifica del numero di figli
    assert(rootNode.get_children_num() == 1);

    // Ottenere il nodo figlio
    Node* retrievedChild = rootNode.getAt(0);
    assert(retrievedChild != nullptr);
    assert(retrievedChild->getType() == "ChildType");

    // Modifica della matrice locale del nodo figlio
    glm::mat4 newLocalMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 3.0f));
    retrievedChild->set_local_matrix(newLocalMatrix);

    // Verifica della traslazione del nodo figlio
    assert(retrievedChild->get_local_matrix() == newLocalMatrix);
}
