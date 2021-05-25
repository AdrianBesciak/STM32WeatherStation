/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MAINVIEWVIEWBASE_HPP
#define MAINVIEWVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/mainview_screen/MainViewPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/SwipeContainer.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class MainViewViewBase : public touchgfx::View<MainViewPresenter>
{
public:
    MainViewViewBase();
    virtual ~MainViewViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::SwipeContainer swipeContainer1;
    touchgfx::Container leftScreen;
    touchgfx::Image bgLeft;
    touchgfx::Image cloud;
    touchgfx::Image drizzle;
    touchgfx::Image full_sun;
    touchgfx::Image haze;
    touchgfx::Image rain;
    touchgfx::Image rain_thunder;
    touchgfx::Image snow;
    touchgfx::Image sun_cloud;
    touchgfx::Image sun_cloud_haze;
    touchgfx::Image sun_rain;
    touchgfx::Image sun_rain_thunder;
    touchgfx::Image thunder;
    touchgfx::ScalableImage owm_temp;
    touchgfx::TextAreaWithOneWildcard currentOWMtemp;
    touchgfx::TextAreaWithOneWildcard currentOWMfeels;
    touchgfx::TextArea current_text_desc;
    touchgfx::TextArea current_text_desc_1;
    touchgfx::ScalableImage hum;
    touchgfx::TextAreaWithOneWildcard humidityText;
    touchgfx::ScalableImage pressureimg;
    touchgfx::TextAreaWithOneWildcard pressureText;
    touchgfx::ScalableImage wind_speed;
    touchgfx::TextAreaWithOneWildcard windSpeed;
    touchgfx::TextAreaWithOneWildcard citynametext;
    touchgfx::TextAreaWithOneWildcard desc;
    touchgfx::Container centerScreen;
    touchgfx::Image bgCenter;
    touchgfx::Container rightScreen;
    touchgfx::Image bgRight;
    touchgfx::ScalableImage temperatureIcon;
    touchgfx::TextAreaWithOneWildcard currentTempValue;
    touchgfx::TextArea currentTempText;
    touchgfx::ScalableImage sunrise;
    touchgfx::ScalableImage sunset;
    touchgfx::TextAreaWithOneWildcard sunsetText;
    touchgfx::TextAreaWithOneWildcard sunriseText;
    touchgfx::ScalableImage visibilityIcon;
    touchgfx::TextAreaWithOneWildcard visibilityText;

    /*
     * Wildcard Buffers
     */
    static const uint16_t CURRENTOWMTEMP_SIZE = 16;
    touchgfx::Unicode::UnicodeChar currentOWMtempBuffer[CURRENTOWMTEMP_SIZE];
    static const uint16_t CURRENTOWMFEELS_SIZE = 16;
    touchgfx::Unicode::UnicodeChar currentOWMfeelsBuffer[CURRENTOWMFEELS_SIZE];
    static const uint16_t HUMIDITYTEXT_SIZE = 8;
    touchgfx::Unicode::UnicodeChar humidityTextBuffer[HUMIDITYTEXT_SIZE];
    static const uint16_t PRESSURETEXT_SIZE = 16;
    touchgfx::Unicode::UnicodeChar pressureTextBuffer[PRESSURETEXT_SIZE];
    static const uint16_t WINDSPEED_SIZE = 16;
    touchgfx::Unicode::UnicodeChar windSpeedBuffer[WINDSPEED_SIZE];
    static const uint16_t CITYNAMETEXT_SIZE = 64;
    touchgfx::Unicode::UnicodeChar citynametextBuffer[CITYNAMETEXT_SIZE];
    static const uint16_t DESC_SIZE = 64;
    touchgfx::Unicode::UnicodeChar descBuffer[DESC_SIZE];
    static const uint16_t CURRENTTEMPVALUE_SIZE = 32;
    touchgfx::Unicode::UnicodeChar currentTempValueBuffer[CURRENTTEMPVALUE_SIZE];
    static const uint16_t SUNSETTEXT_SIZE = 16;
    touchgfx::Unicode::UnicodeChar sunsetTextBuffer[SUNSETTEXT_SIZE];
    static const uint16_t SUNRISETEXT_SIZE = 16;
    touchgfx::Unicode::UnicodeChar sunriseTextBuffer[SUNRISETEXT_SIZE];
    static const uint16_t VISIBILITYTEXT_SIZE = 16;
    touchgfx::Unicode::UnicodeChar visibilityTextBuffer[VISIBILITYTEXT_SIZE];

private:

};

#endif // MAINVIEWVIEWBASE_HPP
