#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <stdio.h>
#include "weather.hpp"


class MainView : public MainViewBase
{
public:
    static constexpr uint8_t MAX_CITY_NAME_LEN = 64;
    static Unicode::UnicodeChar keyboardBuffer[MainView::MAX_CITY_NAME_LEN];

public:
    MainView();
    virtual ~MainView() {}
    void setupScreen() override;
    void tearDownScreen() override;
    virtual void updateTemperatureText(float temp);
    virtual void updateTexts(weather_t* weather);
    virtual void updateWeather(weather_t* weather);

    void on_screen_update() override;

    touchgfx::Image* selectIcon(Weather_t status);
protected:
    touchgfx::Image* prevWeatherIcon;
};

#endif // MAINVIEW_HPP
