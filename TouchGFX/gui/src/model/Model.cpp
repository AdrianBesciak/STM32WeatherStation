#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "ds18b20.hpp"
#include "weather.h"

Model::Model() : modelListener(nullptr), tick_count(0)
{

}

void Model::tick()
{
	tick_count++;

	if(tick_count % 30 == 0){
		const auto& t = thermometers[0];
		if(t.isValid()){
			auto temp = t.getTemperature();
			modelListener->temperatureChanged(temp);
		}
	}

	if(tick_count % 30 == 0){
	    weatherForecast.status = static_cast<Weather_t>((weatherForecast.status + 1) % 5);

		modelListener->weatherChanged(&weatherForecast);
	}
}
