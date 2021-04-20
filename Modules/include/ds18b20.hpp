#pragma once
#include <cstdint>
#include <array>
#include <tuple>
#include <cstdio>
#include <ansi.h>

#include "FreeRTOS.h"

namespace termometer {

    class Ds18b20{
    private:
        uint8_t address_[8];
        float temperature_;
        bool valid_;

    public:
        Ds18b20() noexcept;
        ~Ds18b20() = default;

        [[nodiscard]] uint8_t *getAddress() { return address_; };
        [[nodiscard]] float getTemperature() const { return temperature_; };
        [[nodiscard]] bool isValid() const { return valid_; };

        void setTemperature(float temperature);
        void setValid(bool valid);
    };
}

