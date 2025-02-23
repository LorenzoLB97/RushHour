// test_main.cpp

// Include gli header delle classi di test
#include "Test_DirectionalLight.cpp"
//#include "../../client/tests/Test_GameLogic.cpp" // THIS
#include "Test_Light.cpp"
#include "Test_List.cpp"
#include "Test_Material.cpp"
#include "Test_Mesh.cpp"
#include "Test_Node.cpp"
#include "Test_Object.cpp"
#include "Test_PointLight.cpp"
#include "Test_PrimaryCamera.cpp"
#include "Test_SpotLight.cpp"
#include "Test_Texture.cpp"
#include "Test_engine.cpp"



int main() {
    std::cout << "Inizio" << std::endl;
    testDirectionalLightMethods();
    std::cout << "Finito testDirectionalLightMethods()"<< std::endl;
    //testGameLogicMethods();
    std::cout << "Finito testGameLogicMethods()" << std::endl;
    testLightMethods();
    std::cout << "Finito testLightMethods()" << std::endl;
    testListMethods();
    std::cout << "Finito testListMethods()" << std::endl;
    testMaterialMethods();
    std::cout << "Finito testMaterialMethods()" << std::endl;
    testMeshMethods();
    std::cout << "Finito testMeshMethods()" << std::endl;
    testNodeMethods();
    std::cout << "Finito testNodeMethods()" << std::endl;
    testObjectMethods();
    std::cout << "Finito testObjectMethods()" << std::endl;
    testPointLightMethods();
    std::cout << "Finito testPointLightMethods()" << std::endl;
    testCameraMethods();
    std::cout << "Finito testCameraMethods()" << std::endl;
    testSpotLightMethods();
    std::cout << "Finito testSpotLightMethods()" << std::endl;
    testTextureMethods();
    std::cout << "Finito testTextureMethods()" << std::endl;
    testEngineMethods();
    std::cout << "Fine" << std::endl;

    return 0;
}
