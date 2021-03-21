#ifndef __EPDGUI_WIDGET_ICON_H
#define __EPDGUI_WIDGET_ICON_H

#include "epdgui_widget_graphic_base.h"
#include "ArduinoJson.h"

class EPDGUI_Widget_Icon: public EPDGUI_Widget_Graphic_Base
{

public:
    EPDGUI_Widget_Icon(int16_t x, int16_t y, int16_t w, int16_t h);
    void Render(JsonVariant data);

};


#endif //__EPDGUI_WIDGET_ICON_H