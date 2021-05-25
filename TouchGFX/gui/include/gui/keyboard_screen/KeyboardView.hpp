#ifndef KEYBOARDVIEW_HPP
#define KEYBOARDVIEW_HPP

#include <gui_generated/keyboard_screen/KeyboardViewBase.hpp>
#include <gui/keyboard_screen/KeyboardPresenter.hpp>
#include <gui/common/CustomKeyboard.hpp>

class KeyboardView : public KeyboardViewBase
{
public:
    KeyboardView();
    virtual ~KeyboardView() = default;
    void setupScreen() override;
    void tearDownScreen() override;

    void copy_keyboard_text() override;

    void set_keyboard_text() override;

protected:
    CustomKeyboard keyboard;
};

#endif // KEYBOARDVIEW_HPP
