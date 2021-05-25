#include "../include/weather.hpp"
#include <map>
#include <cstring>

class StrCompare {
public:
    bool operator()(const char *str1, const char *str2) const {
        return std::strcmp(str1, str2) < 0;
    }
};

weather_t weatherForecast;

std::map<const char *, Weather_t, StrCompare> translationMap = {
        {"Clear",        CLEAR},
        {"Clouds",       CLOUDS},
        {"Drizzle",      DRIZZLE},
        {"Fog",          FOG},
        {"Haze",         HAZE},
        {"Rain",         RAIN},
        {"Snow",         SNOW},
        {"Thunderstorm", THUNDERSTORM},
};

Weather_t translate_main_to_enum(const char *data) {
    return translationMap[data];
}

std::map<Weather_Error_t, const char *> errorTranslationMap = {
        {OK,             "Pogoda pobrana"},
        {EMPTY_LOCATION, "Nie podano lokalizacji"},
        {GETHOSTBYNAME,  "Nie udalo sie pobrac adresu serwera"},
        {CONNECT,        "Nie udalo sie polaczyc z serwerem"},
        {SEND,           "Nie udalo sie wyslac zapytania"},
        {RECV_FAIL,      "Nie udalo sie odebrac danych"},
        {RECV_EMPTY,     "Serwer nie zwrocil wynikow"},
        {DOWNLOADING,    "Pobieram..."}
};

const char *error_to_string(Weather_Error_t err) {
    return errorTranslationMap[err];
}