#pragma once
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Meteostation //observable
{
private:
	int humidity;
	int temperature;
	int pressure;
	
public:
	int Get_Humidity()
	{
		humidity = rand() % 90 + 10;
		return humidity;
	}
	int Get_Temperature()
	{
		temperature = rand() % 40;
		return temperature;
	}
	int Get_Pressure()
	{
		pressure = rand() % 100 + 700;
		return pressure;
	}
};

class Sensors
{
public:
	int humidity = 0;
	int temperature = 0;
	int pressure = 0;
};

class IMonitor
{
public:
	virtual void Update(Sensors& obj) = 0;
protected:
	int humidity = 0;
	int temperature = 0;
	int pressure = 0;
};

class Weather_Data //observer
{
private:
	Meteostation* Meteo_station;
	vector<IMonitor*> observers;
	Sensors sensors;
	int count = 0;
public:
	Weather_Data()
	{
		Meteo_station = new Meteostation;
		
	}
	void Update()
	{
		sensors.humidity = Meteo_station->Get_Humidity();
		sensors.temperature = Meteo_station->Get_Temperature();
		sensors.pressure = Meteo_station->Get_Pressure();
		Notify_Observers();
	}
	void Register_Observer(IMonitor* obzer)
	{
		observers.push_back(obzer);
		count++;
	}
	void Remmove_Observer(IMonitor* obzer)
	{
		vector<IMonitor*>::iterator it = remove(observers.begin(), observers.end(), obzer);
		observers.erase(it, observers.end());
		count--;
	}
	void Notify_Observers()
	{
		for (int i = 0; i < count; i++)
		{
			observers[i]->Update(sensors);
		}
		
	}
	~Weather_Data()
	{
		if (Meteo_station != nullptr)
			delete Meteo_station;
	}
};
 

//Датчик показывает текущие значения
class Monitor_Current :public IMonitor
{
private:
	int humidity;
	int temperature;
	int pressure;
	
public:
	void Update(Sensors& obj)
	{
		cout << "\nHumidity is ";
		humidity = humidity + obj.humidity;
		cout << obj.humidity << "%" << endl;
		cout << "\nTemperature is ";
		temperature = temperature + obj.temperature;
		cout << obj.temperature << "C" << endl;
		cout << "\nPressure is ";
		pressure = pressure + obj.pressure;
		cout << obj.pressure << "mm" << endl;
	}
};
//Датчик показывает среднее значение за период обновлений
class Monitor_Statistic :public IMonitor
{
private:
	
	int count = 0;
public:
	void Update(Sensors& obj)
	{
		humidity = humidity + obj.humidity;
		//obj->Get_Humidity();
		temperature = temperature + obj.temperature;
		//obj->Get_Temperature();
		pressure = pressure + obj.pressure;
		//obj->Get_Pressure();
		count++;
	}
	void Show_statistic()
	{
		cout << "\n--------------------------";
		cout << "\nAverage humidity is " << humidity / count << "%";
		cout << "\nAverage temperature is " << temperature / count << "C";
		cout << "\nAverage pressure is " << pressure / count << " mm mercury";
		cout << "\n--------------------------";
	}
};