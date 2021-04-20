#include "../include/lib_ds18b20.h"
#include "../include/ds18b20.hpp"

std::array<termometer::Ds18b20, _DS18B20_MAX_SENSORS> termometers;

extern TaskHandle_t Ds18b20Handle;

std::tuple<uint8_t, OneWire_t> find_termometers(){
    OneWire_t OneWire;
    uint8_t sensorCount;

    uint8_t tries = 5;
    do {
        OneWire_Init(&OneWire, _DS18B20_GPIO, _DS18B20_PIN);
        sensorCount = 0;

        while (HAL_GetTick() < 3000)
            Ds18b20Delay(100);

        uint8_t device = OneWire_First(&OneWire);
        while (device) {
            Ds18b20Delay(100);
            OneWire_GetFullROM(&OneWire, termometers[sensorCount++].getAddress());
            device = OneWire_Next(&OneWire);
        }

        if (sensorCount > 0)
            break;

        tries--;
    } while (tries > 0);

    if (tries == 0) {
        puts(ANSI_FG_RED "[termometers]" ANSI_FG_DEFAULT " not found!");
        vTaskDelete(Ds18b20Handle);
    }

    return std::tuple<uint8_t, OneWire_t>{sensorCount, OneWire};
}

void setup_termometers(uint8_t sensorCount, OneWire_t& OneWire) {
    for (uint8_t i = 0; i < sensorCount; i++) {
        Ds18b20Delay(50);
        DS18B20_SetResolution(&OneWire, termometers[i].getAddress(), DS18B20_Resolution_12bits);
        Ds18b20Delay(50);
        DS18B20_DisableAlarmTemperature(&OneWire, termometers[i].getAddress());
    }
}

extern "C"
[[noreturn]]
void Task_Ds18b20(void *argument) {
    auto&& [sensorCount, OneWire] = find_termometers();
    printf(ANSI_FG_GREEN "[termometers] " ANSI_FG_DEFAULT "Termometers found: %d\n", sensorCount);
    setup_termometers(sensorCount, OneWire);

    for (;;) {
        uint16_t timeoutCounter = _DS18B20_CONVERT_TIMEOUT_MS / 10;

        DS18B20_StartAll(&OneWire);
        osDelay(100);
        while (!DS18B20_AllDone(&OneWire)) {
            osDelay(10);
            timeoutCounter -= 1;
            if (timeoutCounter == 0)
                break;
        }

        if (timeoutCounter > 0) {
            float temperature;
            for (auto i = 0; i < sensorCount; i++) {
                Ds18b20Delay(1000);

                auto valid = DS18B20_Read(&OneWire, termometers[i].getAddress(), &temperature);
                termometers[i].setValid(valid);
                if(valid){
                    termometers[i].setTemperature(temperature);
                }
            }
        } else {
            for (auto i = 0; i < sensorCount; i++) {
                termometers[i].setValid(false);
            }
        }

        for (auto i = 0; i < sensorCount && termometers[i].isValid(); i++) {
            printf("Termometer [%d]:" ANSI_FG_YELLOW " %0.2f*C" ANSI_FG_DEFAULT "\n", i, termometers[i].getTemperature());
        }

        osDelay(_DS18B20_UPDATE_INTERVAL_MS);
    }
}
