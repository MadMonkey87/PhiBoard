#ifndef __PHI_WIDGET_Slider_H
#define __PHI_WIDGET_Slider_H

#include "phi_widget_graphic_base.h"
#include "ArduinoJson.h"
#include "../epdgui_slider.h"

class PHI_Widget_Slider : public PHI_Widget_Graphic_Base
{
public:
    static const int16_t SLIDER_HEIGHT = 60;

public:
    PHI_Widget_Slider(int16_t x, int16_t y, int16_t w, int16_t h);
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_A2); //UPDATE_MODE_DU4, UPDATE_MODE_GC16 
    void Draw(M5EPD_Canvas *canvas);
    void BindEvent(int16_t event, void (* func_cb)(epdgui_args_vector_t&));
    void UpdateTouchState(int16_t x, int16_t y);
    void Render(JsonVariant data);

protected:
    EPDGUI_Slider *_slider = NULL;

private:
    int16_t _state = EVENT_NONE;
    void Render();
};

#endif //__PHI_WIDGET_Slider_H