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

void MainViewView::updateTexts(weather_t* w) {
    Unicode::snprintfFloat(currentOWMtempBuffer, MainViewView::CURRENTOWMTEMP_SIZE, "%2.2f°C", w->temperature);
    currentOWMtemp.invalidate();

    Unicode::snprintfFloat(currentOWMfeelsBuffer, CURRENTOWMFEELS_SIZE, "%2.2f°C", w->feels_like);
    currentOWMfeels.invalidate();

    Unicode::snprintf(humidityTextBuffer, HUMIDITYTEXT_SIZE, "%u%", w->humidity);
    humidityText.invalidate();

    Unicode::snprintf(pressureTextBuffer, PRESSURETEXT_SIZE, "%uhPa", w->pressure);
    pressureText.invalidate();

    Unicode::snprintfFloat(windSpeedBuffer, WINDSPEED_SIZE, "%2.2f m/s", w->wind_speed);
    windSpeed.invalidate();

    Unicode::snprintf(citynametextBuffer, CITYNAMETEXT_SIZE, "%s", w->city);
    citynametext.invalidate();

    Unicode::snprintf(descBuffer, DESC_SIZE, "%uhPa", w->desc);
    desc.invalidate();
}

void MainViewView::updateWeather(weather_t* weather){
    if(prevWeatherIcon){
        prevWeatherIcon->setVisible(false);
        prevWeatherIcon->invalidate();
    }


    touchgfx::Image* newIcon = selectIcon(weather->status);
    newIcon->setVisible(true);
    newIcon->invalidate();

    updateTexts(weather);

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


