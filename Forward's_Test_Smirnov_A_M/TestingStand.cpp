#include "pch.h"
#include "TestingStand.h"
#include "InternalCombustionEngine.h"
#include <iostream>

TestingStand::TestingStand(Engine* engine) {
	this->engine = engine;
}

float TestingStand::getTimeBeforeOverheat() {
	
	thread th(&Engine::StartEngine, engine); // В отдельном потоке начнем симуляцию, а в текущем будем отслеживать момент перегрева.
	th.detach();

	while (engine->isWorking()) {
		if (engine->getT_Engine() >= engine->getT_Overheat()) {
			engine->StopEngine();
			cout << "Температура двигателя в момент перегрева: " << engine->getT_Engine() << " градусов." << endl;
			return engine->getTimeInWork();
		}
	}
	return -1;
}