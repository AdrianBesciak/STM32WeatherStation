#include <gui/mainview_screen/MainViewView.hpp>
#include <stdio.h>

MainViewView::MainViewView()
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
