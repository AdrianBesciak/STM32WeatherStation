#include "../include/weather.hpp"
#include <unordered_map>

weather_t weatherForecast;

std::unordered_map<const char *, Weather_t> translationMap = {
        {"Clear", CLEAR},
        {"Clouds", CLOUDS},
        {"Drizzle", DRIZZLE},
        {"Fog", FOG},
        {"Haze", HAZE},
        {"Rain", RAIN},
        {"Snow", SNOW},
        {"Thunderstorm", THUNDERSTORM},
};

Weather_t translate_main_to_enum(const char * data) {
    return translationMap[data];
}
