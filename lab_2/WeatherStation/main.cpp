#include "WeatherData.h"
int main()
{
	CWeatherData wd;
	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);
	CTemperatureStatsDisplay temperatureStatsDisplay;
	wd.RegisterObserver(temperatureStatsDisplay);

	CHumidityStatsDisplay humidityStatsDisplay;
	wd.RegisterObserver(humidityStatsDisplay);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd.RemoveObserver(statsDisplay);
	wd.RemoveObserver(temperatureStatsDisplay);

	CPressureStatsDisplay pressureStatsDisplay;
	wd.RegisterObserver(pressureStatsDisplay);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);
	return 0;
}