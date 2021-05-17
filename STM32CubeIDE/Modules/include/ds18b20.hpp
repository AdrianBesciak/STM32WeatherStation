#pragma once
#include <cstdint>
#include <array>
#include <tuple>
#include <cstdio>
#include <ansi.h>
#include <ds18b20Config.h>

class Ds18b20;
extern std::array<Ds18b20, _DS18B20_MAX_SENSORS> thermometers;

class Ds18b20 {
private:
	static constexpr float TEMPERATURE_CORRECTION = 4.0;

	uint8_t address_[8];
	float temperature_;
	bool valid_;

public:
	Ds18b20() noexcept;
	~Ds18b20() = default;

	[[nodiscard]] uint8_t* getAddress();
	[[nodiscard]] float getTemperature() const;
	[[nodiscard]] bool isValid() const;
	void setTemperature(float temperature);
};

