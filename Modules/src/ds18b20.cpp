#include "../include/ds18b20.hpp"

namespace termometer {

    Ds18b20::Ds18b20() noexcept:
            address_{},
            temperature_(0.0),
            valid_(false) {
    }

    void Ds18b20::setTemperature(float temperature) {
        temperature_ = temperature;
    }

    void Ds18b20::setValid(bool valid) {
        valid_ = valid;
    }
}
