#pragma once
#include "Engine.h"
#include <vector>

class InternalCombustionEngine : public Engine {
public:
	InternalCombustionEngine(int T_Ambient);
	InternalCombustionEngine(int T_Ambient, int I, int T_Overheat, std::vector<int> M, std::vector<int> V, float Hm, float Hv, float C);
	~InternalCombustionEngine() override;

	void StartEngine() override; // ��������� ��������� � �������� ����������
	void StopEngine() override; // ������������� ��������� � ���������
	bool isWorking() override;
	void setWorking(bool working) override;
	int getT_Engine() override;
	int getT_Overheat() override;
	int getTimeInWork() override; // �������� ����� ������ ���������

private:
	int i = 0; // ���-�� ��������� �� �������.
	float T_Engine; // ����������� ���������
	float Vh; // �������� ������� ���������
	float Vc; // �������� ���������� ���������
	float timeInWork = 0; // ����� ������ ���������

	struct PointOfTime
	{
		float m, v, a, sec; // �������� ������, �������� �������� � ��������� � ������ ����� �������, ����� �������� �� ����� ����� � ������
	};

	std::vector<PointOfTime> points;

	int T_Ambient; // ����������� ���������� �����
	int I; // ������ ������� ���������
	int T_Overheat; // ����������� ���������
	std::vector<int> M; // �������� ������, �������������� ����������
	std::vector<int> V; // �������� �������� ���������
	float Hm; // ����������� ����������� �������� ������� �� ��������� �������
	float Hv; // ����������� ����������� �������� ������� �� �������� �������� ���������
	float C; // ����������� ����������� �������� ���������� �� ����������� ��������� � ���������� �����
};