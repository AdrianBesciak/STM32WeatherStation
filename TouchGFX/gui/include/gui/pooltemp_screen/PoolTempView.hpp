#ifndef POOLTEMP_VIEW_HPP
#define POOLTEMP_VIEW_HPP

#include <gui_generated/pooltemp_screen/PoolTempViewBase.hpp>
#include <gui/pooltemp_screen/PoolTempPresenter.hpp>

class PoolTempView : public PoolTempViewBase
{
public:
    PoolTempView();
    virtual ~PoolTempView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    //event from Presenter
    virtual void refreshTemperature();
};

#endif // POOLTEMP_VIEW_HPP
