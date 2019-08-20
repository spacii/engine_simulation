#include "pch.h"
#include "TestingStand.h"
#include "InternalCombustionEngine.h"
#include <iostream>

TestingStand::TestingStand(Engine* engine) {
	this->engine = engine;
}

float TestingStand::getTimeBeforeOverheat() {
	
	thread th(&Engine::StartEngine, engine); // � ��������� ������ ������ ���������, � � ������� ����� ����������� ������ ���������.
	th.detach();

	while (engine->isWorking()) {
		if (engine->getT_Engine() >= engine->getT_Overheat()) {
			engine->StopEngine();
			cout << "����������� ��������� � ������ ���������: " << engine->getT_Engine() << " ��������." << endl;
			return engine->getTimeInWork();
		}
	}
	return -1;
}