#include "../include/lib_ds18b20.h"
#include "../include/ds18b20.hpp"

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

        //INFO: remove disabling IRQ's if problematic
        __disable_irq();
        uint8_t device = OneWire_First(&OneWire);
        while (device) {
            Ds18b20Delay(100);
            OneWire_GetFullROM(&OneWire, thermometers[sensorCount++].getAddress());
            device = OneWire_Next(&OneWire);
        }
        __enable_irq();

        if (sensorCount > 0)
            break;

        tries--;
        printf(ANSI_FG_RED "[Thermometers]" ANSI_FG_DEFAULT " tries left: %d\n", tries);
    } while (tries > 0);

    if (tries == 0) {
        puts(ANSI_FG_RED "[Thermometers]" ANSI_FG_DEFAULT " not found!");
        vTaskDelete(Ds18b20Handle);
    }

    return std::tuple<uint8_t, OneWire_t>{sensorCount, OneWire};
}

void setup_termometers(uint8_t sensorCount, OneWire_t& OneWire) {
    for (uint8_t i = 0; i < sensorCount; i++) {
        Ds18b20Delay(50);
        DS18B20_SetResolution(&OneWire, thermometers[i].getAddress(), DS18B20_Resolution_12bits);
        Ds18b20Delay(50);
        DS18B20_DisableAlarmTemperature(&OneWire, thermometers[i].getAddress());
    }
}

extern "C"
[[noreturn]]
void Task_Ds18b20(void *argument) {
    auto&& [sensorCount, OneWire] = find_termometers();
    printf(ANSI_FG_GREEN "[Thermometers] " ANSI_FG_DEFAULT "Thermometers found: %d\n", sensorCount);
    setup_termometers(sensorCount, OneWire);

    float temperature;
    for (;;) {
        uint16_t timeoutCounter = _DS18B20_CONVERT_TIMEOUT_MS / 10;

        DS18B20_StartAll(&OneWire);
        Ds18b20Delay(100);
        while (!DS18B20_AllDone(&OneWire)) {
        	Ds18b20Delay(10);
            timeoutCounter -= 1;
            if (timeoutCounter == 0)
                break;
        }

        if (timeoutCounter > 0) {
            for(auto& t: thermometers) {
                Ds18b20Delay(1000);

                //INFO: remove disabling IRQ's if problematic
                __disable_irq();
                auto invalid = DS18B20_Read(&OneWire, t.getAddress(), &temperature);
                __enable_irq();
                if(!invalid){
                    t.setTemperature(temperature);
                    printf("Thermometer:" ANSI_FG_YELLOW " %0.2f*C" ANSI_FG_DEFAULT "\n", t.getTemperature());
                }
            }
        }
        Ds18b20Delay(_DS18B20_UPDATE_INTERVAL_MS);
    }
}
