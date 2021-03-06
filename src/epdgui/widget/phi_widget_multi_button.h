#ifndef __PHI_WIDGET_Multi_Button_H
#define __PHI_WIDGET_Multi_Button_H

#include "phi_widget_base.h"
#include "../epdgui_button.h"
#include "ArduinoJson.h"
#include <list>

class PHI_Widget_Multi_Button : public PHI_Widget_Base
{
public:
    static const int16_t SEPARATOR_HEIGHT = 2;
    static const int16_t SEPARATOR_HORIZONTAL_MARGIN = 10;
    static const int16_t SEPARATOR_COLOR = 6;

public:
    PHI_Widget_Multi_Button(int16_t x, int16_t y, int16_t w, int16_t h, int16_t items);
    ~PHI_Widget_Multi_Button();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_GC16); //UPDATE_MODE_DU4
    void Draw(M5EPD_Canvas *canvas);
    void BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &));
    void UpdateTouchState(int16_t x, int16_t y);
    void Render(JsonVariant data);

private:
    std::list<EPDGUI_Button *> _buttons;
    void RenderButtonContent(M5EPD_Canvas *canvas, bool pressed, String description, String icon, bool first, bool last);
};

#endif //__PHI_WIDGET_Multi_Button_H