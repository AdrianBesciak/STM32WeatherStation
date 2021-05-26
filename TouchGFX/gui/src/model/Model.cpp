#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "ds18b20.hpp"
#include "weather.hpp"

Model::Model() : modelListener(nullptr), tick_count(0) {

}

void mockData() {
    weatherForecast.status = static_cast<Weather_t>((weatherForecast.status + 1) % 5);
    weatherForecast.temperature += 0.1;
    weatherForecast.feels_like += 0.2;
    weatherForecast.humidity = (weatherForecast.humidity + 1) % 100;
    weatherForecast.pressure++;
    weatherForecast.wind_speed += 0.1;
    weatherForecast.sunset += 2137;
    weatherForecast.sunrise += 1337;
    weatherForecast.visibility += 0.1;

//    weatherForecast.error = static_cast<Weather_Error_t>((weatherForecast.error + 1) % (RECV_EMPTY + 1));
}

void Model::tick() {
    if (tick_count % 60 == 0) {
        const auto &t = thermometers[0];
        if (t.isValid()) {
            auto temp = t.getTemperature();
            modelListener->temperatureChanged(temp);
        }
    }

    if (tick_count % 60 == 0) {
//        mockData();

        modelListener->weatherChanged(&weatherForecast);
    }

    tick_count++;
}
