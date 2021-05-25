#ifndef KEYBOARDPRESENTER_HPP
#define KEYBOARDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class KeyboardView;

class KeyboardPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    KeyboardPresenter(KeyboardView& v);

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

    virtual ~KeyboardPresenter() {};

private:
    KeyboardPresenter();

    KeyboardView& view;
};

#endif // KEYBOARDPRESENTER_HPP
