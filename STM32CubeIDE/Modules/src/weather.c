#include "../include/weather.h"
#include "string.h"

weather_t weatherForecast;

Weather_t getMainWeather(const char * data) {
	if (strcmp(data, "Clear") == 0) {
		return CLEAR;
	}
	if (strcmp(data, "Clouds") == 0) {
		return CLOUDS;
	}
	if (strcmp(data, "Drizzle") == 0) {
		return DRIZZLE;
	}
	if (strcmp(data, "Fog") == 0) {
		return FOG;
	}
	if (strcmp(data, "Haze") == 0) {
		return HAZE;
	}
	if (strcmp(data, "Rain") == 0) {
		return RAIN;
	}
	if (strcmp(data, "Snow") == 0) {
		return SNOW;
	}
	if (strcmp(data, "Thunderstorm") == 0) {
		return THUNDERSTORM;
	}

	return CLEAR; //defaults to clear
}

float getFloatValue(const char * data) {
	float value = 0.0;
	int denominator = 0;
	int i = 0;
	while (i < strlen(data) && !(data[i] == ',' || data[i] == '}')) {
		if (data[i] == '.')
			denominator = 10;
		else if (!denominator)
			value = value * 10 + (data[i] - '0');
		else {
			value += ((float)(data[i] - '0')) / denominator;
			denominator *= 10;
		}
		i++;
	}
	return value;
}
