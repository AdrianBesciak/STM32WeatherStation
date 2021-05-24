#include <gui/mainview_screen/MainViewView.hpp>
#include <stdio.h>

MainViewView::MainViewView() : prevWeatherIcon(nullptr)
{

}

void MainViewView::setupScreen()
{
    MainViewViewBase::setupScreen();
}

void MainViewView::tearDownScreen()
{
    MainViewViewBase::tearDownScreen();
}

void MainViewView::updateTemperatureText(float temp){
	Unicode::snprintfFloat(currentTempValueBuffer, MainViewView::CURRENTTEMPVALUE_SIZE, "%2.2f°C", temp);
	currentTempValue.invalidate();
}

void MainViewView::updateWeather(weather_t* weather){
    if(prevWeatherIcon){
        prevWeatherIcon->setVisible(false);
        prevWeatherIcon->invalidate();
    }

    touchgfx::Image* newIcon = selectIcon(weather->status);
    newIcon->setVisible(true);
    newIcon->invalidate();

    prevWeatherIcon = newIcon;
}

touchgfx::Image *MainViewView::selectIcon(Weather_t status) {
    switch (status) {
        case CLEAR:
            return &full_sun;
        case CLOUDS:
            return &sun_cloud;
        case DRIZZLE:
            return &drizzle;
        case FOG:
            return &sun_cloud_haze;
        case HAZE:
            return &haze;
        case RAIN:
            return &rain;
        case SNOW:
            return &snow;
        case THUNDERSTORM:
            return &rain_thunder;
    }

    printf("selectIcon missing switch value\n");
    return nullptr;
}
