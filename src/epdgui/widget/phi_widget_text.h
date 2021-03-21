#ifndef __PHI_WIDGET_Text_H
#define __PHI_WIDGET_Text_H

#include "phi_widget_graphic_base.h"
#include "ArduinoJson.h"

class PHI_Widget_Text : public PHI_Widget_Graphic_Base
{

public:
    PHI_Widget_Text(int16_t x, int16_t y, int16_t w, int16_t h);
    void Render(JsonVariant data);
};

#endif //__PHI_WIDGET_Text_H