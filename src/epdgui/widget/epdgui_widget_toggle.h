#ifndef __EPDGUI_WIDGET_Toggle_H
#define __EPDGUI_WIDGET_Toggle_H

#include "epdgui_widget_graphic_base.h"
#include "ArduinoJson.h"

class EPDGUI_Widget_Toggle : public EPDGUI_Widget_Graphic_Base
{
public:
    static const int16_t TOGGLE_WIDTH = 120;
    static const int16_t TOGGLE_HEIGHT = 60;
    static const int16_t TOGGLE_CORNER_RADIUS = 30;
    static const int16_t TOGGLE_BORDER_WIDTH = 4;
    static const int16_t TOGGLE_BORDER_COLOR = 12;
    static const int16_t TOGGLE_BACKGROUND_COLOR = 4;

    static const int16_t TOGGLE_KNOB_WIDTH = 56;
    static const int16_t TOGGLE_KNOB_HEIGHT = 56;
    static const int16_t TOGGLE_KNOB_COLOR = 15;
    static const int16_t TOGGLE_KNOB_CORNER_RADIUS = 27;

public:
    EPDGUI_Widget_Toggle(int16_t x, int16_t y, int16_t w, int16_t h);
    void Bind(int16_t event, void (* func_cb)(epdgui_args_vector_t&));
    void UpdateState(int16_t x, int16_t y);
    void Init(JsonVariant data);
    void Render(JsonVariant data);

private:
    bool _value = false;
    int16_t _state = EVENT_NONE;
    void Render();
};

#endif //__EPDGUI_WIDGET_Toggle_H