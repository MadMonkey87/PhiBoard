#ifndef __PHI_WIDGET_ICON_TOGGLE_H
#define __PHI_WIDGET_ICON_TOGGLE_H

#include "phi_widget_graphic_base.h"
#include "ArduinoJson.h"

class PHI_Widget_Icon_Toggle : public PHI_Widget_Graphic_Base
{

public:
    PHI_Widget_Icon_Toggle(int16_t x, int16_t y, int16_t w, int16_t h);
    void Init(JsonVariant data);
    void Render(JsonVariant data);

private:
    JsonArray _items;
    int16_t _index = 0;
    int16_t _state = EVENT_NONE;
    void Render();
};

#endif //__PHI_WIDGET_ICON_TOGGLE_H