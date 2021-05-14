#pragma once
#include <cstdint>
#include <array>
#include <tuple>
#include <cstdio>
#include <ansi.h>
#include <ds18b20Config.h>

#include "FreeRTOS.h"

class Ds18b20;
extern std::array<Ds18b20, _DS18B20_MAX_SENSORS> thermometers;

class Ds18b20 {
private:
	uint8_t address_[8];
	float temperature_;

public:
	Ds18b20() noexcept;
	~Ds18b20() = default;

	[[nodiscard]] uint8_t* getAddress() {
		return address_;
	}

	[[nodiscard]] float getTemperature() const {
		return temperature_;
	}

	void setTemperature(float temperature);
};

