#include <gui/main_screen/MainView.hpp>

Unicode::UnicodeChar MainView::keyboardBuffer[MainView::MAX_CITY_NAME_LEN] = {};

MainView::MainView() : prevWeatherIcon(nullptr)
{
    desc.setWideTextAction(touchgfx::WIDE_TEXT_WORDWRAP);
    currentTempText.setWideTextAction(touchgfx::WIDE_TEXT_WORDWRAP);
    checkWeatherButton.setTouchable(false);
}

void MainView::setupScreen()
{
    MainViewBase::setupScreen();
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}

void MainView::updateTemperatureText(float temp){
    Unicode::snprintfFloat(currentTempValueBuffer, MainView::CURRENTTEMPVALUE_SIZE, "%2.2f°C", temp);
    currentTempValue.invalidate();
}

void MainView::updateTexts(weather_t* w) {
    Unicode::snprintfFloat(currentOWMtempBuffer, MainView::CURRENTOWMTEMP_SIZE, "%2.2f°C", w->temperature);
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

    char tempBuffer[0x20];
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

void MainView::updateWeather(weather_t* weather){
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

touchgfx::Image *MainView::selectIcon(Weather_t status) {
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

void MainView::on_screen_update() {
    if(Unicode::strlen(MainView::keyboardBuffer) > 0){
        Unicode::strncpy(inputFieldBuffer, MainView::keyboardBuffer, INPUTFIELD_SIZE);
        inputField.invalidate();
        checkWeatherButton.setTouchable(true);
    }else{
        checkWeatherButton.setTouchable(false);
    }
    checkWeatherButton.invalidate();
}

void MainView::get_new_weather() {
    //TODO: get new data from API
}


