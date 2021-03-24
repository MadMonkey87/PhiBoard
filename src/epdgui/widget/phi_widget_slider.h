#ifndef __PHI_WIDGET_Slider_H
#define __PHI_WIDGET_Slider_H

#include "phi_widget_graphic_base.h"
#include "ArduinoJson.h"

class PHI_Widget_Slider : public PHI_Widget_Graphic_Base
{
public:

public:
    PHI_Widget_Slider(int16_t x, int16_t y, int16_t w, int16_t h);
    void BindEvent(int16_t event, void (* func_cb)(epdgui_args_vector_t&));
    void UpdateTouchState(int16_t x, int16_t y);
    void Init(JsonVariant data);
    void Render(JsonVariant data);

private:
    bool _value = false;
    int16_t _state = EVENT_NONE;
    void Render();
};

#endif //__PHI_WIDGET_Slider_H