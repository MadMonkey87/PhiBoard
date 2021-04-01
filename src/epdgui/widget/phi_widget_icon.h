#ifndef __PHI_WIDGET_ICON_H
#define __PHI_WIDGET_ICON_H

#include "phi_widget_graphic_base.h"
#include "ArduinoJson.h"

struct Widget_Icon_Definition : Widget_Base_Definition
{
    public:
    Icon_Definition *Icon;
    String Description;
    PhiAction_Definition *PhiAction;
};

class PHI_Widget_Icon : public PHI_Widget_Graphic_Base
{

public:
    PHI_Widget_Icon(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Icon_Definition *definition);
    void Render();

protected:
    Widget_Icon_Definition *_definition;
    PhiAction_Definition *GetPhiAction();
};

#endif //__PHI_WIDGET_ICON_H