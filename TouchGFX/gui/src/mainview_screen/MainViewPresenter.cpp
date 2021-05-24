#include <gui/mainview_screen/MainViewView.hpp>
#include <gui/mainview_screen/MainViewPresenter.hpp>

MainViewPresenter::MainViewPresenter(MainViewView& v)
    : view(v)
{

}

void MainViewPresenter::activate()
{

}

void MainViewPresenter::deactivate()
{

}

void MainViewPresenter::temperatureChanged(float new_temp){
	view.updateTemperatureText(new_temp);
}

void MainViewPresenter::weatherChanged(weather_t* weatherStruct){
	view.updateWeather(weatherStruct);
}
