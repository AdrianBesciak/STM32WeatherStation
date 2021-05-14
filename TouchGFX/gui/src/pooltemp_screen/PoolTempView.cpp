#include <gui/pooltemp_screen/PoolTempView.hpp>
#include <ds18b20.hpp>

PoolTempView::PoolTempView()
{
}

void PoolTempView::setupScreen()
{
}

void PoolTempView::tearDownScreen()
{
}

void PoolTempView::refreshTemperature(){
	float temp = thermometers[0].getTemperature();
    Unicode::snprintfFloat(tempTextBuffer, PoolTempView::TEMPTEXT_SIZE, "%2.2f", temp);

    tempText.invalidate();
}
