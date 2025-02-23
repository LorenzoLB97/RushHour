#include "../List.h"
#include "../DirectionalLight.h"
#include "../PointLight.h"
#include <cassert>
#

void testListMethods() {
    
    // Creazione di alcuni oggetti di test


    /*
    Node root("Root", "RootNode");
    Node child1("Child", "ChildNode1");
    Node child2("Child", "ChildNode1");
    DirectionalLight directionalLight("DirectionalLight1");
    PointLight pointLight("PointLight2");
     
    Node* root = new Node("Root", "RootNode");
    Node* child1 = new Node("Child", "ChildNode1");
    Node* child2 = new Node("Child", "ChildNode2");
    Node* directionalLight = new DirectionalLight("DirectionalLight1");
    Node* pointLight = new PointLight("PointLight2");
    
    // Creazione dell'oggetto List di test
    List nodeList;

    // Aggiunta dei nodi alla lista
    nodeList.addNode(&root);
    nodeList.addNode(&child1);
    nodeList.addNode(&child2);
    nodeList.addNode(&directionalLight);
    nodeList.addNode(&pointLight);

    std::cout << "nodeList.size() " << nodeList.size() << std::endl;
    // Verifica della dimensione della lista
    assert(nodeList.size() == 5);   // come mai da 0?

    // questo fallisce di conseguenza
    std::cout << "nodeList.findById(child1->getID()) " << nodeList.findById(child1.getID()) << std::endl;
    // Verifica della ricerca di un nodo per ID
    //assert(nodeList.findById(child1.getID()) == child1);

    // Pulizia della lista
    nodeList.clear();

    std::cout << "nodeList.size() " << nodeList.size() << std::endl;
    // Verifica della dimensione dopo la pulizia
    assert(nodeList.size() == 0);

    // Deallocazione della memoria per gli oggetti di test
    /*
    delete root;
    delete child1;
    delete child2;
    delete light1;
    delete light2;
    */
}

