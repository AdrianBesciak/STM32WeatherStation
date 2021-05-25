#include <gui/keyboard_screen/KeyboardView.hpp>
#include <gui/main_screen/MainView.hpp>

KeyboardView::KeyboardView()
{
    keyboard.setPosition(80, 16, 320, 240);
    add(keyboard);
    keyboard.invalidate();
}

void KeyboardView::setupScreen()
{
    KeyboardViewBase::setupScreen();
}

void KeyboardView::tearDownScreen()
{
    KeyboardViewBase::tearDownScreen();
}

void KeyboardView::copy_keyboard_text() {
    Unicode::UnicodeChar *buffer = keyboard.getBuffer();
    if(Unicode::strlen(buffer) > 0){
        Unicode::strncpy(MainView::keyboardBuffer, buffer, MainView::MAX_CITY_NAME_LEN);
    }
}

void KeyboardView::set_keyboard_text() {
    Unicode::UnicodeChar *buffer = keyboard.getBuffer();
    if(Unicode::strlen(MainView::keyboardBuffer) > 0){
        Unicode::strncpy(buffer, MainView::keyboardBuffer, MainView::MAX_CITY_NAME_LEN);
        keyboard.setBufferPosition(Unicode::strlen(buffer));
        keyboard.capslockPressedHandler(); //if we have something in buffer then switch to lowercase
    }
}

