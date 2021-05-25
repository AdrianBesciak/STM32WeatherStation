#include <gui/mainview_screen/MainViewView.hpp>

MainViewView::MainViewView() : prevWeatherIcon(nullptr)
{
    desc.setWideTextAction(touchgfx::WIDE_TEXT_WORDWRAP);
    currentTempText.setWideTextAction(touchgfx::WIDE_TEXT_WORDWRAP);
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

static char tempBuffer[0x20];
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

    Unicode::fromUTF8(reinterpret_cast<const uint8_t *>(w->city), citynametextBuffer, CITYNAMETEXT_SIZE);
    citynametext.invalidate();

    Unicode::fromUTF8(reinterpret_cast<const uint8_t *>(w->desc), descBuffer, CITYNAMETEXT_SIZE);
    desc.invalidate();

    tm *timeinfo = localtime(&w->sunrise);
    strftime(tempBuffer, 0x100, "%H:%M:%S", timeinfo);
    Unicode::strncpy(sunriseTextBuffer, tempBuffer, SUNRISETEXT_SIZE);
    sunriseText.invalidate();

    timeinfo = localtime(&w->sunset);
    strftime(tempBuffer, 0x100, "%H:%M:%S", timeinfo);
    Unicode::strncpy(sunsetTextBuffer, tempBuffer, SUNSETTEXT_SIZE);
    sunsetText.invalidate();

    Unicode::snprintfFloat(visibilityTextBuffer, VISIBILITYTEXT_SIZE, "%2.2fkm", w->visibility);
    visibilityText.invalidate();
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


