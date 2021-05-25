#include <gui/main_screen/MainView.hpp>
#include <gui/main_screen/MainPresenter.hpp>

MainPresenter::MainPresenter(MainView& v)
    : view(v)
{

}

void MainPresenter::activate()
{

}

void MainPresenter::deactivate()
{

}

void MainPresenter::temperatureChanged(float new_temp){
    view.updateTemperatureText(new_temp);
}

void MainPresenter::weatherChanged(weather_t* weatherStruct){
    view.updateWeather(weatherStruct);
}
