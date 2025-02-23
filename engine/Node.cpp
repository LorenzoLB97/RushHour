
#include "Node.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut.h>
#include <glm/gtc/type_ptr.hpp>

Node::Node(const std::string& type, const std::string& name)
	: m_parent{ nullptr }
	, Object(type, name)
{
	m_localMatrix = glm::mat4(1.0f);
	m_globalMatrix = glm::mat4(1.0f);
}

void Node::set_local_matrix(const glm::mat4& matrix) {
	m_localMatrix = matrix;
	m_globalMatrix = getFinalMatrix();
	updateGlobalMatrices();
}

glm::mat4 Node::get_local_matrix() const {
	return m_localMatrix;
}

void Node::add_child(std::unique_ptr<Node> child) {
	child->m_parent = this; 
	child->m_globalMatrix = child->getFinalMatrix();
	m_children.emplace_back(std::move(child)); 
	updateGlobalMatrices();
}

void Node::updateGlobalMatrices() {
	m_globalMatrix = getFinalMatrix();
	for (auto& child : m_children) {
		child->m_globalMatrix = child->getFinalMatrix();
		child->updateGlobalMatrices();
	}
}

Node* Node::get_parent() const {
	return m_parent;
}

std::size_t Node::get_children_num() const {
	return m_children.size();
}

void Node::rendering(const glm::mat4& inverse_camera) const {}

Node* Node::getAt(std::size_t idx) {
	if (m_children.empty() || idx >= m_children.size()) return nullptr;
	return m_children[idx].get();
}

void Node::translate(const glm::vec3& translation) {
	m_localMatrix = glm::translate(m_localMatrix, translation);
	m_globalMatrix = getFinalMatrix();
}

glm::mat4 Node::getFinalMatrix() const {
	glm::mat4 finalMatrix = glm::mat4(1.0f);

	const Node* currentNode = this; // this = most derived subclass
	while (currentNode != nullptr) {
		finalMatrix = currentNode->m_localMatrix * finalMatrix;
		currentNode = currentNode->m_parent;
	}

	return finalMatrix;
}

Node* Node::findNodeById(std::size_t id) {
	if (id == getID()) return this;

	for (auto& child : m_children) {
		Node* find = child->findNodeById(id);
		if (find != nullptr) return find;
	}

	return nullptr;
}