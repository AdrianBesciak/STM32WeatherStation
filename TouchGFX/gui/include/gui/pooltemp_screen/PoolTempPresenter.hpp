#ifndef POOLTEMP_PRESENTER_HPP
#define POOLTEMP_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class PoolTempView;

class PoolTempPresenter : public Presenter, public ModelListener
{
public:
    PoolTempPresenter(PoolTempView& v);
    virtual ~PoolTempPresenter() {};

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

private:
    PoolTempPresenter();

    PoolTempView& view;
};

#endif // POOLTEMP_PRESENTER_HPP
