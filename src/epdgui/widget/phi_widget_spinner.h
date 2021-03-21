#ifndef __PHI_WIDGET_Spinner_H
#define __PHI_WIDGET_Spinner_H

#include "phi_widget_base.h"
#include "../epdgui_button.h"
#include "ArduinoJson.h"

class PHI_Widget_Spinner : public PHI_Widget_Base
{
public:
    static const int16_t BUTTON_HEIGHT = 80;

public:
    PHI_Widget_Spinner(int16_t x, int16_t y, int16_t w, int16_t h);
    void Bind(int16_t event, void (*func_cb)(epdgui_args_vector_t &));
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_GC16); //UPDATE_MODE_DU4
    void Draw(M5EPD_Canvas *canvas);
    void UpdateState(int16_t x, int16_t y);
    void Render(JsonVariant data);

protected:
    EPDGUI_Button *_centralButton = NULL;
    EPDGUI_Button *_leftButton = NULL;
    EPDGUI_Button *_rightButton = NULL;

private:
    void RenderCenterButton(M5EPD_Canvas *canvas, bool pressed, String description, String value);
    void RenderLeftButton(M5EPD_Canvas *canvas, bool pressed, String icon);
    void RenderRightButton(M5EPD_Canvas *canvas, bool pressed, String icon);
};

#endif //__PHI_WIDGET_Spinner_H