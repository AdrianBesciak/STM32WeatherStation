#ifndef MAINVIEWVIEW_HPP
#define MAINVIEWVIEW_HPP

#include <gui_generated/mainview_screen/MainViewViewBase.hpp>
#include <gui/mainview_screen/MainViewPresenter.hpp>
#include <chrono>
#include <stdio.h>
#include "weather.hpp"


class MainViewView : public MainViewViewBase
{
public:
    MainViewView();
    virtual ~MainViewView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void updateTemperatureText(float temp);
    virtual void updateTexts(weather_t* weather);
    virtual void updateWeather(weather_t* weather);
    touchgfx::Image* selectIcon(Weather_t status);
protected:
    touchgfx::Image* prevWeatherIcon;
};

#endif // MAINVIEWVIEW_HPP
