
#include "Object.h"

Object::Object(const std::string& type, const std::string& name)
    : m_id(idGenerator++), m_type(type), m_objectName(name) 
{
}

std::size_t Object::getID() const { 
    return m_id; 
}

const std::string& Object::getType() const { 
    return m_type; 
}

const std::string& Object::getName() const { 
    return m_objectName; 
}

void Object::setType(const std::string& type) {
    this->m_type = type;
}

glm::vec4 Object::generateUniqueColor() const {
    return glm::vec4(m_id, m_id, m_id, 255);
}
