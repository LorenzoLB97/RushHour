// tests/Test_GameLogic.cpp

#include "../GameLogic.h"
/*
    case 101: SU
	case 103: GIU
    case 102: DESTRA
	case 100: SINISTRA
	    
*/

void testFirstLevel(){
    GameLogic gameLogic(1);

    // Verifica della vittoria
    assert(gameLogic.checkVictory() == false);

    // Test del movimento dell'auto
    assert(gameLogic.moveAuto("AutoV003", 103) == false);
    assert(gameLogic.moveAuto("AutoL004", 102) == true);  
    assert(gameLogic.moveAuto("AutoL004", 102) == true);   
    assert(gameLogic.moveAuto("AutoL004", 102) == false);

    assert(gameLogic.moveAuto("AutoL008G", 102) == true);
    assert(gameLogic.moveAuto("AutoL008G", 102) == true);
    assert(gameLogic.moveAuto("AutoL008G", 102) == true);
    assert(gameLogic.moveAuto("AutoL008G", 102) == false);

    assert(gameLogic.moveAuto("AutoV003", 101) == true);
    assert(gameLogic.moveAuto("AutoV003", 101) == false);

    assert(gameLogic.moveAuto("AutoL006", 100) == true);
    assert(gameLogic.moveAuto("AutoL006", 100) == false);

    assert(gameLogic.moveAuto("AutoV001", 101) == true);
    assert(gameLogic.moveAuto("AutoV001", 101) == true);
    assert(gameLogic.moveAuto("AutoV001", 101) == true);
    assert(gameLogic.moveAuto("AutoV001", 101) == true);

    // Testa la funzione di vittoria
    assert(gameLogic.checkVictory() == true);
}

void testSecondLevel() {
    GameLogic gameLogic(2);

    // Verifica della vittoria
    assert(gameLogic.checkVictory() == false);

    // Test del movimento dell'auto
    assert(gameLogic.moveAuto("AutoV003", 103) == true);

    assert(gameLogic.moveAuto("AutoV002", 103) == true);
    assert(gameLogic.moveAuto("AutoV002", 103) == true);
    assert(gameLogic.moveAuto("AutoV002", 103) == false);

    assert(gameLogic.moveAuto("AutoL006", 100) == true);
    assert(gameLogic.moveAuto("AutoL006", 100) == true);
    assert(gameLogic.moveAuto("AutoL006", 100) == false);

    assert(gameLogic.moveAuto("AutoL005", 100) == true);

    assert(gameLogic.moveAuto("AutoV007G", 103) == true);

    assert(gameLogic.moveAuto("AutoL008G", 102) == true);

    assert(gameLogic.moveAuto("AutoV001", 101) == true);
    assert(gameLogic.moveAuto("AutoV001", 101) == true);
    assert(gameLogic.moveAuto("AutoV001", 101) == true);
    assert(gameLogic.moveAuto("AutoV001", 101) == true);

    // Testa la funzione di vittoria
    assert(gameLogic.checkVictory() == true);
}

void testThirdLevel() {
    GameLogic gameLogic(3);

    // Verifica della vittoria
    assert(gameLogic.checkVictory() == false);

    // Test del movimento dell'auto
    assert(gameLogic.moveAuto("AutoV003", 103) == true);

    assert(gameLogic.moveAuto("AutoL007G", 102) == true);

    assert(gameLogic.moveAuto("AutoV001", 101) == true);

    assert(gameLogic.moveAuto("AutoL006", 102) == true);

    assert(gameLogic.moveAuto("AutoV002", 103) == true);
    assert(gameLogic.moveAuto("AutoV002", 103) == true);
    assert(gameLogic.moveAuto("AutoV002", 103) == false);
    assert(gameLogic.moveAuto("AutoV004", 103) == true);
    assert(gameLogic.moveAuto("AutoV004", 103) == true);
    assert(gameLogic.moveAuto("AutoV004", 103) == false);

    assert(gameLogic.moveAuto("AutoL005", 100) == true);
    assert(gameLogic.moveAuto("AutoL005", 100) == false);
    
    assert(gameLogic.moveAuto("AutoV001", 101) == true);
    assert(gameLogic.moveAuto("AutoV001", 101) == true);

    // Testa la funzione di vittoria
    assert(gameLogic.checkVictory() == true);  // Verifica se la vittoria è stata raggiunta
}
void testGameLogicMethods(){
    testFirstLevel();
    testSecondLevel();
    testThirdLevel();
}