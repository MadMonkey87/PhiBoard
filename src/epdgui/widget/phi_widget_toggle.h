#ifndef __PHI_WIDGET_Toggle_H
#define __PHI_WIDGET_Toggle_H

#include "phi_widget_graphic_base.h"
#include "ArduinoJson.h"
#include "../epdgui_toggle.h"

struct Widget_Toggle_Definition : Widget_Base_Definition
{
public:
    String Description;
    PhiAction_Definition *PhiAction;
};

class PHI_Widget_Toggle : public PHI_Widget_Graphic_Base
{
public:
    static const int16_t TOGGLE_WIDTH = 120;
    static const int16_t TOGGLE_HEIGHT = 60;

public:
    PHI_Widget_Toggle(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Toggle_Definition *definition);
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_A2); //UPDATE_MODE_DU4, UPDATE_MODE_GC16
    void Draw(M5EPD_Canvas *canvas);
    void BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &));
    void UpdateTouchState(int16_t x, int16_t y);
    void Render();

protected:
    EPDGUI_Toggle *_toggle = NULL;
    Widget_Toggle_Definition *_definition;
    PhiAction_Definition *GetPhiAction();
};

#endif //__PHI_WIDGET_Toggle_H