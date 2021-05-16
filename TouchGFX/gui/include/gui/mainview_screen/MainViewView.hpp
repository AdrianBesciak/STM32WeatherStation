#ifndef MAINVIEWVIEW_HPP
#define MAINVIEWVIEW_HPP

#include <gui_generated/mainview_screen/MainViewViewBase.hpp>
#include <gui/mainview_screen/MainViewPresenter.hpp>

class MainViewView : public MainViewViewBase
{
public:
    MainViewView();
    virtual ~MainViewView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void updateTemperatureText(float temp);
protected:
};

#endif // MAINVIEWVIEW_HPP
