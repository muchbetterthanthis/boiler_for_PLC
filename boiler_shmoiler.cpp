#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <string>

void initiateSimulation(int& waterLevel, const int& lowLevelSet, const int& highLevelSet, bool& lowLevel, bool& highLevel);
void updateSimulation(int& waterLevel, const int& lowLevelSet, const int& highLevelSet, bool& lowLevel, bool& highLevel);
void simulation(int& waterLevel, const int& lowLevelSet, int& sleepTime, const int& highLevelSet, bool& pump);
void raiseWaterLevelOnce(int& waterLevel);
void lowerWaterLevelOnce(int& waterLevel);
void showStartParam(const int& lowLevelSet, const int& highLevelSet);
void showParam(int& waterLevel, bool lowLevel, bool highLevel, bool pump);


int main()
{
	int waterLevel = 0;
	int lowLevelSet = 10;
	int highLevelSet = 50;
	int sleepTime = 3;
	bool lowLevel = false;
	bool highLevel = false;
	bool pump = false;
	char continueSimulation = 'y';

	showStartParam(lowLevelSet, highLevelSet);

	while (continueSimulation == 'y') {
		initiateSimulation(waterLevel, lowLevelSet, highLevelSet, lowLevel, highLevel);
		showParam(waterLevel, lowLevel, highLevel, pump);

		for (int i = 0; i != sleepTime; i++) {
			Sleep(1000);
			std::cout << ".";
		}
		std::cout << std::endl;

		simulation(waterLevel, lowLevelSet, sleepTime, highLevelSet, pump);
		
		do {
			std::cout << "Continue? [y/n]" << std::endl;
			std::cin >> continueSimulation;
		} while (!std::cin.fail() && continueSimulation != 'y' && continueSimulation != 'n');
	}

	system("pause");
}

void initiateSimulation(int& waterLevel, const int& lowLevelSet, const int& highLevelSet, bool& lowLevel, bool& highLevel) {
	int randomWaterLevel = rand() % 100 + 1;

	waterLevel = randomWaterLevel;

	randomWaterLevel >= lowLevelSet ? lowLevel = true : lowLevel = false;
	randomWaterLevel >= highLevelSet ? highLevel = true : highLevel = false;
}

void updateSimulation(int& waterLevel, const int& lowLevelSet, const int& highLevelSet, bool& lowLevel, bool& highLevel) {
	waterLevel >= lowLevelSet ? lowLevel = true : lowLevel = false;
	waterLevel >= highLevelSet ? highLevel = true : highLevel = false;
}

void simulation(int& waterLevel, const int& lowLevelSet, int& sleepTime, const int& highLevelSet, bool& pump) {
	if (waterLevel < lowLevelSet) {
		while (waterLevel != lowLevelSet)
		{
			showParam(waterLevel, false, false, true);

			std::cout << "raising water level to current set... (" << waterLevel << "/" << lowLevelSet << ")" << std::endl;
			raiseWaterLevelOnce(waterLevel);
		}

		showParam(waterLevel, true, false, pump);
	}

	if (waterLevel > highLevelSet) {
		std::cout << "exceeding of the upper value!" << std::endl;

		for (int i = 0; i != sleepTime; i++) {
			Sleep(1000);
			std::cout << ".";
		}

		std::cout << std::endl;

		while (waterLevel >= highLevelSet)
		{
			showParam(waterLevel, true, true, true);
			std::cout << "raising water level to current set... (" << waterLevel << "/" << highLevelSet << ")" << std::endl;
			lowerWaterLevelOnce(waterLevel);
		}

		showParam(waterLevel, true, false, pump);
	}
}

void raiseWaterLevelOnce(int& waterLevel) {
	waterLevel += 1;
}

void lowerWaterLevelOnce(int& waterLevel) {
	waterLevel -= 1;
}

void showStartParam(const int& lowLevelSet, const int& highLevelSet) {
	std::cout << "---INITIAL PARAMETERS---" << std::endl;
	std::cout << "Low level set: " << lowLevelSet << std::endl;
	std::cout << "High level set: " << highLevelSet << std::endl;
}

//void showParam(int& waterLevel, bool& lowLevel, bool& highLevel, bool& pump) {
//	std::string lowLevelSensor = lowLevel  ? "ON" : "OFF";
//	std::string highLevelSensor = highLevel ? "ON" : "OFF";
//	std::string pumpIs = pump ? "ON" : "OFF";
//
//	std::cout << "------------------" << std::endl;
//	std::cout << "Current water level: " << waterLevel << std::endl;
//	std::cout << "low level sensor: " << lowLevelSensor << std::endl;
//	std::cout << "high level sensor: " << highLevelSensor << std::endl;
//	std::cout << "pump: " << pumpIs << std::endl;
//}

void showParam(int& waterLevel, bool lowLevel, bool highLevel, bool pump) {
	std::string lowLevelSensor = lowLevel ? "ON" : "OFF";
	std::string highLevelSensor = highLevel ? "ON" : "OFF";
	std::string pumpIs = pump ? "ON" : "OFF";

	std::cout << "------------------" << std::endl;
	std::cout << "Current water level: " << waterLevel << std::endl;
	std::cout << "low level sensor: " << lowLevelSensor << std::endl;
	std::cout << "high level sensor: " << highLevelSensor << std::endl;
	std::cout << "pump: " << pumpIs << std::endl;
}