#pragma once
#include <stdint.h>

typedef enum Weather_t {
    CLEAR = 0,
    CLOUDS,
    DRIZZLE,
    FOG,
    HAZE,
    RAIN,
    SNOW,
    THUNDERSTORM
} Weather_t;

constexpr uint32_t MAX_DESCRIPTION_LEN =    64;
constexpr uint32_t MAX_CITY_NAME =          64;
constexpr uint32_t MAX_MAIN_NAME =          64;

typedef struct weather_t {
    double lon, lat;                            // coords
    double temperature;                         // in celsius
    double feels_like;                          // in celsius
    uint32_t pressure;                          // hPa
    uint32_t humidity;                          // %
    uint32_t visibility;                        // m
    double wind_speed;                          // m/s
    uint32_t sunrise, sunset;                   // linux timestamp
    Weather_t status;                           // enum status
    char main[MAX_MAIN_NAME];                   // main weather text
    char desc[MAX_DESCRIPTION_LEN];	            // in PL
    char city[MAX_CITY_NAME];                   // city name

} weather_t;

extern weather_t weatherForecast;

Weather_t translate_main_to_enum(const char * data);
