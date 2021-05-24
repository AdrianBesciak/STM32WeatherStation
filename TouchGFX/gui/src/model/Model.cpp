#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "ds18b20.hpp"
#include "weather.hpp"

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

	if(tick_count % 50 == 0){
	    //FIXME: remove this, only for testing
	    weatherForecast.status = static_cast<Weather_t>((weatherForecast.status + 1) % 5);
        weatherForecast.temperature += 0.1;

		modelListener->weatherChanged(&weatherForecast);
	}
}
