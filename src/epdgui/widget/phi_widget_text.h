#ifndef __PHI_WIDGET_Text_H
#define __PHI_WIDGET_Text_H

#include "phi_widget_graphic_base.h"
#include "ArduinoJson.h"

struct Widget_Text_Definition : Widget_Base_Definition
{
    String Description;
    String Value;
    String Hint;
    PhiAction_Definition *PhiAction;
};

class PHI_Widget_Text : public PHI_Widget_Graphic_Base
{

public:
    PHI_Widget_Text(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Text_Definition *definition);
    void Render();

protected:
    Widget_Text_Definition *_definition;
    PhiAction_Definition *GetPhiAction();
};

#endif //__PHI_WIDGET_Text_H