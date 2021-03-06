/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef MAINVIEWBASE_HPP
#define MAINVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/SwipeContainer.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>

class MainViewBase : public touchgfx::View<MainPresenter>
{
public:
    MainViewBase();
    virtual ~MainViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void on_screen_update()
    {
        // Override and implement this function in Main
    }

    virtual void get_new_weather()
    {
        // Override and implement this function in Main
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::SwipeContainer swipeContainer1;
    touchgfx::Container centerScreen;
    touchgfx::Image bgLeft;
    touchgfx::TextArea cityNameFieldLabel;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > inputButton;
    touchgfx::TextAreaWithOneWildcard inputField;
    touchgfx::ButtonWithLabel checkWeatherButton;
    touchgfx::TextArea statusText;
    touchgfx::TextAreaWithOneWildcard statusTextArea;
    touchgfx::Container leftScreen;
    touchgfx::Image bgCenter;
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
    static const uint16_t INPUTFIELD_SIZE = 64;
    touchgfx::Unicode::UnicodeChar inputFieldBuffer[INPUTFIELD_SIZE];
    static const uint16_t STATUSTEXTAREA_SIZE = 64;
    touchgfx::Unicode::UnicodeChar statusTextAreaBuffer[STATUSTEXTAREA_SIZE];
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

    /*
     * Callback Declarations
     */
    touchgfx::Callback<MainViewBase, const touchgfx::AbstractButton&> buttonCallback;
    touchgfx::Callback<MainViewBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);

};

#endif // MAINVIEWBASE_HPP
