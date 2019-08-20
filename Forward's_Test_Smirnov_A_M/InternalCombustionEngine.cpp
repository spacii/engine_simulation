#include "pch.h"
#include "InternalCombustionEngine.h"
#include <iostream>

using namespace std;

InternalCombustionEngine::InternalCombustionEngine(int T_Ambient) {
	this->T_Engine = T_Ambient;
}

InternalCombustionEngine::InternalCombustionEngine(int T_Ambient, int I, int T_Overheat, vector<int> M, vector<int> V, float Hm, float Hv, float C) {
	this->T_Engine = T_Ambient;
	this->I = I;
	this->T_Overheat = T_Overheat;
	this->M = M;
	this->V = V;
	this->Hm = Hm;
	this->Hv = Hv;
	this->C = C;
}

InternalCombustionEngine::~InternalCombustionEngine() {
	
}

int InternalCombustionEngine::getT_Engine() {
	return T_Engine;
}

int InternalCombustionEngine::getT_Overheat() {
	return T_Overheat;
}

void InternalCombustionEngine::StartEngine() {

	setWorking(true); // «апускаем двигатель

	int grafPoints = M.size(); //  оличество заданных вершин графика
	int currentPoint = 0, iter = 0; // currentPoint - текущай вершина на графике. iter - текуща€ точка графика после вершины
	int x1, x2, y1, y2, currentX = 0; //x1, x2, y1, y2 - X и Y двух точек через которые проходит пр€ма€. currentX = текущий X

	while (isWorking()) {

		x1 = V[currentPoint];
		y1 = M[currentPoint];
		x2 = V[currentPoint + 1];
		y2 = M[currentPoint + 1];

		currentX = x1 + iter; // “екущий икс равен текущей вершине + смещение от нее
		float y = (((currentX - x1) * (y2 - y1)) / (x2 - x1)) + y1;

		PointOfTime temp;
		temp.m = y;
		temp.v = currentX;
		temp.a = y / I;

		points.push_back(temp);

		if (points.size() != 1) { // ≈сли не перва€ точка на графике, то расчитываем врем€ перехода
			points[points.size() - 1].sec = (points[points.size() - 1].v - points[points.size() - 2].v) / points[points.size() - 1].a;
		}
		else {
			points[points.size() - 1].sec = 0; // ≈сли перва€, то приравниваем к нулю
		}

		Vh = points[points.size() - 1].m * Hm + (points[points.size() - 1].v * points[points.size() - 1].v) * Hv;
		Vc = C * (T_Ambient - T_Engine);
		T_Engine = T_Engine + Vh - Vc;

		timeInWork += points[points.size() - 1].sec; // —колько уже проработал двигатель

		if (currentX+1 == x2) { // ≈сли следующий X равен иксу заданной в параметрах симул€ции вершины графика, то мен€ем текущую вершину на новую
			if (currentPoint+1 == grafPoints - 1) { // ѕровер€ем будет ли данна€ вершина последней заданной в параметрах симул€ции
				StopEngine(); // ≈сли да, то завершаем симул€цию и останавливаем двигатель
			}
			else {
				currentPoint++; // ≈сли нет, то смещаем текущую вершину и продолжаем симул€цию.
				iter = 0; // ќбнул€ем текущую точку после вершины
			}
		}
		else {
			iter++; // ≈сли не достигли новой вершины, увеличиваем смещение 
		}
	}
}

void InternalCombustionEngine::StopEngine() {
	setWorking(false);
}

bool InternalCombustionEngine::isWorking() {
	return this->working;
}

void InternalCombustionEngine::setWorking(bool working) {
	this->working = working;
}

int InternalCombustionEngine::getTimeInWork() {
	return timeInWork;
}