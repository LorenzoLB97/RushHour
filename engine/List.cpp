

#include <glm/fwd.hpp>
#include <glm/matrix.hpp>
#include <GL/freeglut.h>

#include "List.h"
#include "Node.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"


void List::addNode(Node* root) {
    Node* node = root->getAt(0); // root ignored (getAt(0) = first child)

    for (std::size_t i = 1; i <= root->get_children_num(); ++i) {
        if (Light* v = dynamic_cast<Light*>(node)) {
            if (v->getLightNumber() <= GL_LIGHT7)
                m_instances.push_front(node);
        }
        else m_instances.push_back(node);

        if (node && node->get_children_num() > 0) {
            addNode(node);
        }
        node = root->getAt(i);
    }
}

void List::rendering(const glm::mat4& camera) const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (const auto& node : m_instances) {
        if (DirectionalLight* directionalLight = dynamic_cast<DirectionalLight*>(node))
            directionalLight->rendering(camera);
        else if (PointLight* pointLight = dynamic_cast<PointLight*>(node))
            pointLight->rendering(camera);
        else if (SpotLight* spotLight = dynamic_cast<SpotLight*>(node))
            spotLight->rendering(camera);
        else if (node)
            node->rendering(camera);
    }
}

Node* List::findById(std::size_t ID) const {
    Node* n;
    for (const auto& current : m_instances) {
        n = current->findNodeById(ID);
        if (n) return n;
    }
    return nullptr;
}

Node* List::getNode(std::size_t idx) const {
    for (std::size_t counter = 0; const auto& node : m_instances) {
        if (counter == idx) return node;
        ++counter;
    }
    return nullptr;
}

void List::clear()
{
    /*
    std::list<Node*>::iterator it;
    //Render each list element
    for (it = instances.begin(); it != instances.end(); it++)
    {
        Light* v;
        if ((v = dynamic_cast<Light*>(*it)))
            delete (Light*)(*it);
        else
            delete (*it);
    }
    */
    m_instances.clear();
}



std::size_t List::size() const {
    return m_instances.size();
}