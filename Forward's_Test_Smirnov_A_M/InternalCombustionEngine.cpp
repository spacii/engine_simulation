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

	setWorking(true); // ��������� ���������

	int grafPoints = M.size(); // ���������� �������� ������ �������
	int currentPoint = 0, iter = 0; // currentPoint - ������� ������� �� �������. iter - ������� ����� ������� ����� �������
	int x1, x2, y1, y2, currentX = 0; //x1, x2, y1, y2 - X � Y ���� ����� ����� ������� �������� ������. currentX = ������� X

	while (isWorking()) {

		x1 = V[currentPoint];
		y1 = M[currentPoint];
		x2 = V[currentPoint + 1];
		y2 = M[currentPoint + 1];

		currentX = x1 + iter; // ������� ��� ����� ������� ������� + �������� �� ���
		float y = (((currentX - x1) * (y2 - y1)) / (x2 - x1)) + y1;

		PointOfTime temp;
		temp.m = y;
		temp.v = currentX;
		temp.a = y / I;

		points.push_back(temp);

		if (points.size() != 1) { // ���� �� ������ ����� �� �������, �� ����������� ����� ��������
			points[points.size() - 1].sec = (points[points.size() - 1].v - points[points.size() - 2].v) / points[points.size() - 1].a;
		}
		else {
			points[points.size() - 1].sec = 0; // ���� ������, �� ������������ � ����
		}

		Vh = points[points.size() - 1].m * Hm + (points[points.size() - 1].v * points[points.size() - 1].v) * Hv;
		Vc = C * (T_Ambient - T_Engine);
		T_Engine = T_Engine + Vh - Vc;

		timeInWork += points[points.size() - 1].sec; // ������� ��� ���������� ���������

		if (currentX+1 == x2) { // ���� ��������� X ����� ���� �������� � ���������� ��������� ������� �������, �� ������ ������� ������� �� �����
			if (currentPoint+1 == grafPoints - 1) { // ��������� ����� �� ������ ������� ��������� �������� � ���������� ���������
				StopEngine(); // ���� ��, �� ��������� ��������� � ������������� ���������
			}
			else {
				currentPoint++; // ���� ���, �� ������� ������� ������� � ���������� ���������.
				iter = 0; // �������� ������� ����� ����� �������
			}
		}
		else {
			iter++; // ���� �� �������� ����� �������, ����������� �������� 
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