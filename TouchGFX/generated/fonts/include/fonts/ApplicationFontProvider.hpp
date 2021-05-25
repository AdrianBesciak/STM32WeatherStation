/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#ifndef APPLICATIONFONTPROVIDER_HPP
#define APPLICATIONFONTPROVIDER_HPP

#include <touchgfx/FontManager.hpp>

namespace touchgfx
{
    class FlashDataReader;
}

struct Typography
{
    static const touchgfx::FontId DEFAULT = 0;
    static const touchgfx::FontId TEMPERATURE_WILDCARD = 1;
    static const touchgfx::FontId SMALL_FONT = 2;
    static const touchgfx::FontId OWM_STYLE = 3;
    static const touchgfx::FontId OWM_STYLE_20 = 4;
    static const touchgfx::FontId DISPLAY = 5;
    static const touchgfx::FontId KEYBOARD = 6;
    static const touchgfx::FontId MODE = 7;
    static const touchgfx::FontId BUTTON_LABELS = 8;
};

struct TypographyFontIndex
{
    static const touchgfx::FontId DEFAULT = 0;              // verdanab_26_4bpp
    static const touchgfx::FontId TEMPERATURE_WILDCARD = 1; // verdanab_28_4bpp
    static const touchgfx::FontId SMALL_FONT = 2;           // verdana_25_4bpp
    static const touchgfx::FontId OWM_STYLE = 2;            // verdana_25_4bpp
    static const touchgfx::FontId OWM_STYLE_20 = 3;         // verdana_20_4bpp
    static const touchgfx::FontId DISPLAY = 4;              // RobotoCondensed_Regular_28_4bpp
    static const touchgfx::FontId KEYBOARD = 5;             // RobotoCondensed_Regular_20_4bpp
    static const touchgfx::FontId MODE = 6;                 // RobotoCondensed_Regular_24_4bpp
    static const touchgfx::FontId BUTTON_LABELS = 7;        // verdanab_12_4bpp
    static const uint16_t NUMBER_OF_FONTS = 8;
};

class ApplicationFontProvider : public touchgfx::FontProvider
{
public:
    virtual touchgfx::Font* getFont(touchgfx::FontId typography);

    static void setFlashReader(touchgfx::FlashDataReader* /* flashReader */) { }
    static touchgfx::FlashDataReader* getFlashReader() { return 0; }
};

#endif // APPLICATIONFONTPROVIDER_HPP
