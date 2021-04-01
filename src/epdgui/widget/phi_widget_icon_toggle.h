#ifndef __PHI_WIDGET_ICON_TOGGLE_H
#define __PHI_WIDGET_ICON_TOGGLE_H

#include "phi_widget_graphic_base.h"
#include "ArduinoJson.h"

struct Widget_Icon_Toggle_Definition : Widget_Base_Definition
{
};

class PHI_Widget_Icon_Toggle : public PHI_Widget_Graphic_Base
{

public:
    PHI_Widget_Icon_Toggle(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Icon_Toggle_Definition *definition);
    void Init();
    void Render();

protected:
    Widget_Icon_Toggle_Definition *_definition;
    PhiAction_Definition *GetPhiAction();

private:
    int16_t _index = 0;
    int16_t _state = EVENT_NONE;
    void RenderInternal();
};

#endif //__PHI_WIDGET_ICON_TOGGLE_H