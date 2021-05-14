#include "../include/ds18b20.hpp"

std::array<Ds18b20, _DS18B20_MAX_SENSORS> thermometers;

Ds18b20::Ds18b20() noexcept :
		address_ { }, temperature_(0.0){
}

void Ds18b20::setTemperature(float temperature) {
	temperature_ = temperature;
}
