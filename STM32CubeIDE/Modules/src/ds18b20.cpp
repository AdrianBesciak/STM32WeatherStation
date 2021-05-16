#include "../include/ds18b20.hpp"

std::array<Ds18b20, _DS18B20_MAX_SENSORS> thermometers;

Ds18b20::Ds18b20() noexcept :
		address_ { },
		temperature_(0.0),
		valid_(false)
		{
}

void Ds18b20::setTemperature(float temperature) {
	temperature_ = temperature;
	valid_ = true;
}

float Ds18b20::getTemperature() const {
	if(!valid_){
		return 0.0;
	}
	return temperature_ - Ds18b20::TEMPERATURE_CORRECTION;
}

uint8_t* Ds18b20::getAddress() {
	return address_;
}

bool Ds18b20::isValid() const {
	return valid_;
}
