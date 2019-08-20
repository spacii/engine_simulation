#pragma once
#include "Engine.h"
#include <thread>

using namespace std;

class TestingStand {
public:
	TestingStand(Engine* engine);
	float getTimeBeforeOverheat();
private:
	Engine* engine;
};