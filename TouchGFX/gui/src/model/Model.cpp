#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <ds18b20.hpp>

Model::Model() : modelListener(0), tick_count(0)
{

}

void Model::tick()
{
	tick_count++;

	if(tick_count % 30){
		return;
	}

	const auto& t = thermometers[0];
	if(t.isValid()){
		auto temp = t.getTemperature();
		modelListener->temperatureChanged(temp);
	}
}
