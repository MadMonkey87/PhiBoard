#ifndef __PHI_WIDGET_Double_Switch_H
#define __PHI_WIDGET_Double_Switch_H

#include "phi_widget_graphic_base.h"
#include "../epdgui_button.h"
#include "ArduinoJson.h"

class PHI_Widget_Double_Switch : public PHI_Widget_Graphic_Base
{
public:
    static const int16_t MIDDLE_HEIGHT = 16;
    static const int16_t BAR_HEIGHT = 2;
    static const int16_t BAR_HORIZONTAL_MARGIN = 10;
    static const int16_t BAR_COLOR = 6;

public:
    PHI_Widget_Double_Switch(int16_t x, int16_t y, int16_t w, int16_t h);
    ~PHI_Widget_Double_Switch();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_GC16); //UPDATE_MODE_DU4
    void Draw(M5EPD_Canvas *canvas);
    void Bind(int16_t event, void (*func_cb)(epdgui_args_vector_t &));
    void UpdateTouchState(int16_t x, int16_t y);
    void Render(JsonVariant data);

protected:
    EPDGUI_Button *_upperButton = NULL;
    EPDGUI_Button *_lowerButton = NULL;

private:
    void RenderUpperButton(M5EPD_Canvas *canvas, bool pressed, String icon);
    void RenderLowerButton(M5EPD_Canvas *canvas, bool pressed, String icon);
};

#endif //__PHI_WIDGET_Double_Switch_H