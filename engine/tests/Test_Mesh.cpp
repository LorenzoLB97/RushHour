// tests/Mesh_test.cpp

#include "../Mesh.h"
#include "../Material.h"
#include <iostream>
#include <cassert>

void MeshConstructorTest() {
    Mesh mesh("test_mesh");
    assert(mesh.getName() == "test_mesh");
    assert(mesh.getMaterial() == nullptr);
}

void MeshMaterialTest() {
    std::shared_ptr<Material> material = std::make_shared<Material>("test_material");
    Mesh mesh("test_mesh");
    mesh.setMaterial(material);
    assert(mesh.getMaterial() == material.get());
}

void testMeshMethods() {
    // Esegui tutti i test
    MeshConstructorTest();
    MeshMaterialTest();
}