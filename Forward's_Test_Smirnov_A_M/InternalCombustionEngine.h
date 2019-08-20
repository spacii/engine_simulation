#pragma once
#include "Engine.h"
#include <vector>

class InternalCombustionEngine : public Engine {
public:
	InternalCombustionEngine(int T_Ambient);
	InternalCombustionEngine(int T_Ambient, int I, int T_Overheat, std::vector<int> M, std::vector<int> V, float Hm, float Hv, float C);
	~InternalCombustionEngine() override;

	void StartEngine() override; // Запускаем двигатель и начинаем симульяцию
	void StopEngine() override; // Останавливаем двигатель и симуляцию
	bool isWorking() override;
	void setWorking(bool working) override;
	int getT_Engine() override;
	int getT_Overheat() override;
	int getTimeInWork() override; // Получить время работы двигателя

private:
	int i = 0; // Кол-во переходов по графику.
	float T_Engine; // Температура двигателя
	float Vh; // Скорость нагрева двигателя
	float Vc; // Скорость охлаждения двигателя
	float timeInWork = 0; // Время работы двигателя

	struct PointOfTime
	{
		float m, v, a, sec; // крутящий момент, скорость вращения и ускорение в данной точке графика, время перехода от одной точки к другой
	};

	std::vector<PointOfTime> points;

	int T_Ambient; // Температура окружающей среды
	int I; // Момент инерции двигателя
	int T_Overheat; // Температура перегрева
	std::vector<int> M; // Крутящий момент, вырабатываемый двигателем
	std::vector<int> V; // Скорость вращения коленвала
	float Hm; // Коэффициент зависимости скорости нагрева от крутящего момента
	float Hv; // Коэффициент зависимости скорости нагрева от скорости вращения коленвала
	float C; // Коэффициент зависимости скорости охлаждения от температуры двигателя и окружающей среды
};