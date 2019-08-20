// Forward's_Test_Smirnov_A_M.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "TestingStand.h"
#include "InternalCombustionEngine.h"
#include <thread>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void printOverheatTestResult(int result) {
	if (result == -1) {
		cout << "В ходе данного теста двигатель не перегрелся." << endl;
	}
	else {
		cout << "Выбранный тип двигателя перегреется при заданной температуре окружающей среды через: " << result << " секунд." << endl;
	}
}

void doOverheatTestWithUserSettings(int T_Ambient, int I, int T_Overheat, vector<int> M, vector<int> V, float Hm, float Hv, float C) {
	InternalCombustionEngine* ICE = new InternalCombustionEngine(T_Ambient, I, T_Overheat, M, V, Hm, Hv, C);
	TestingStand* testingStand = new TestingStand(ICE);
	printOverheatTestResult(testingStand->getTimeBeforeOverheat());
}

void doOverheatTestWithDefaultSettings(int T_Ambient) {
	InternalCombustionEngine* ICE = new InternalCombustionEngine(T_Ambient, 10, 110, vector<int> {20, 75, 100, 105, 75, 0}, vector<int> {0, 75, 150, 200, 250, 300}, 0.01, 0.0001, 0.1);
	TestingStand* testingStand = new TestingStand(ICE);
	printOverheatTestResult(testingStand->getTimeBeforeOverheat());
}

int main()
{
	setlocale(LC_ALL, "Russian");
	
	int T_Ambient, engineType, testType;
	int engineTypes[] = { 1 }, ICEtestTypes[] = { 1 }; // Сюда вносятся ID соответствующие опредленному типу двигателя и ID соответствующие опредленному тесту
	string sT_Ambient, sengineType, stestType;

	ifstream input("config.txt");

	cout << "Введите температуру окружающей среды в градусах Цельсия: ";
	cin >> sT_Ambient;

	while (true) { // Проверка на корректность температуры. Должно быть число
		try {
			T_Ambient = stoi(sT_Ambient);
			break;
		}
		catch (const std::exception& e) {
			cout << "Введено некорректное значение!Попробуйте снова! Ввод: "; cin >> sT_Ambient;
		}
	}

	cout << "Выберите тип двигателя для симмуляции. Для выбора введите соответствующее значение: [ДВС] - 1: ";
	cin >> sengineType;

	while (true) { // Проверка на корректрость и наличие такого типа двигателей
		bool good = false;
		try {
			engineType = stoi(sengineType);
			for (int i = 0; i < sizeof(engineTypes) / sizeof(int); i++) {
				if (engineType == engineTypes[i]) {
					good = true;
					break;
				}
			}
			if (good == true) {
				break;
			}
			else {
				cout << "Такого типа не существует в базе двигателей! Попроуйте снова! Ввод: "; cin >> sengineType;
			}			
		}
		catch (const std::exception& e) {
			cout << "Введено некорректное значение!Попробуйте снова! Ввод: "; cin >> sengineType;
		}
	}

	switch (engineType) { // Выбор типа двигателя
		case 1: {

			cout << "Выберите тест. Для выбора введите соответствующее значение: [Получение времени перегрева] - 1: ";
			cin >> stestType;

			while (true) { // Проверка на корректрость и наличие такого теста
				bool good = false;
				try {
					testType = stoi(stestType);
					for (int i = 0; i < sizeof(ICEtestTypes) / sizeof(int); i++) {
						if (testType == ICEtestTypes[i]) {
							good = true;
							break;
						}
					}
					if (good == true) {
						break;
					}
					else {
						cout << "Такого теста не существует! Попроуйте снова! Ввод: "; cin >> stestType;
					}
				}
				catch (const std::exception& e) {
					cout << "Введено некорректное значение!Попробуйте снова! Ввод: "; cin >> stestType;
				}
			}

			switch (testType) { // Выбор теста для выбранного типа двигателя
				case 1: {
					if (input.is_open()) { // Проверка на наличие конфигурационного файла

						string sI, sT_Overheat, sarraySize, sHm, sHv, sC;
						vector<string> sM, sV;

						int I, T_Overheat, arraySize;
						vector<int> M, V;
						float Hm, Hv, C;

						input >> sI; 
						input >> sT_Overheat;
						input >> sarraySize;

						try {
							arraySize = stoi(sarraySize);
						} catch (const std::exception& e) {
							cout << "В конфигурационный файл были введены некорректные данные. Данные будут заполненые автоматически значениями по умолчанию." << endl;
							doOverheatTestWithDefaultSettings(T_Ambient);
						}

						for (int i = 0; i < arraySize; i++) {
							string temp;
							input >> temp; input.ignore(1);
							sM.push_back(temp);
						}
						for (int i = 0; i < arraySize; i++) {
							string temp;
							input >> temp; input.ignore(1);
							sV.push_back(temp);
						}

						input >> sHm;
						input >> sHv;
						input >> sC;

						try { // Блок проверки значений из файла на соответствие необходимого типа данных для симуляции. Проверка всех переменных происходит в одном блоке, а не при считывание каждой, чтобы не тратить много места на трай-кэтчи в коде
							I = stoi(sI);
							T_Overheat = stoi(sT_Overheat);

							for (int i = 0; i < arraySize; i++) {
								float temp = stof(sM[i]);
								M.push_back(temp);
							}
							for (int i = 0; i < arraySize; i++) {
								float temp = stof(sV[i]);
								V.push_back(temp);
							}

							Hm = stof(sHm);
							Hv = stof(sHv);
							C = stof(sC);

							cout << "Параметры для симуляции успешно считаны из конфигурационного файла." << endl;
							doOverheatTestWithUserSettings(T_Ambient, I, T_Overheat, M, V, Hm, Hv, C);
						}
						catch (const std::exception& e) { // Если какая-либо переменная не соответствует
							cout << "В конфигурационный файл были введены некорректные данные. Данные будут заполненые автоматически значениями по умолчанию." << endl;
							doOverheatTestWithDefaultSettings(T_Ambient);
						}
					}
					else {
						cout << "Файл конфигурации не найден. Данные будут заполненые автоматически значениями по умолчанию." << endl;
						doOverheatTestWithDefaultSettings(T_Ambient);
					}
				} break;
				default :
					break;
			}

		} break;

		default:
			break;
	}
	return 0;
}
