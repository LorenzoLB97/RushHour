// tests/engine_test.cpp

#include "../engine.h"
#include <iostream>
#include <cassert>

void EngineConstructorTest() {
    Engine engine;

    // Verifica che il motore sia inizializzato correttamente
    assert(engine.getList().size() == 0);
}


void testEngineMethods() {
    EngineConstructorTest();
}