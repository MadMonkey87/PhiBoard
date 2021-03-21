#ifndef __EPDGUI_WIDGET_Double_Switch_H
#define __EPDGUI_WIDGET_Double_Switch_H

#include "epdgui_widget_graphic_base.h"
#include "../epdgui_button.h"
#include "ArduinoJson.h"

class EPDGUI_Widget_Double_Switch : public EPDGUI_Widget_Graphic_Base
{
public:
    static const int16_t MIDDLE_HEIGHT = 16;
    static const int16_t BAR_HEIGHT = 2;
    static const int16_t BAR_HORIZONTAL_MARGIN = 10;
    static const int16_t BAR_COLOR = 6;

public:
    EPDGUI_Widget_Double_Switch(int16_t x, int16_t y, int16_t w, int16_t h);
    ~EPDGUI_Widget_Double_Switch();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_GC16); //UPDATE_MODE_DU4
    void Draw(M5EPD_Canvas *canvas);
    void Bind(int16_t event, void (*func_cb)(epdgui_args_vector_t &));
    void UpdateState(int16_t x, int16_t y);
    void Render(JsonVariant data);

protected:
    EPDGUI_Button *_upperButton = NULL;
    EPDGUI_Button *_lowerButton = NULL;

private:
    void RenderUpperButton(M5EPD_Canvas *canvas, bool pressed, String icon);
    void RenderLowerButton(M5EPD_Canvas *canvas, bool pressed, String icon);
};

#endif //__EPDGUI_WIDGET_Double_Switch_H