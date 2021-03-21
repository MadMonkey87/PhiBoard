#ifndef __EPDGUI_WIDGET_GRAPHIC_BASE_H
#define __EPDGUI_WIDGET_GRAPHIC_BASE_H

#include "epdgui_widget_base.h"
#include "ArduinoJson.h"

class EPDGUI_Widget_Graphic_Base : public EPDGUI_Widget_Base
{

public:
    EPDGUI_Widget_Graphic_Base(int16_t x, int16_t y, int16_t w, int16_t h, boolean createNormalCanvas, boolean createPressedCanvas);
    ~EPDGUI_Widget_Graphic_Base();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_A2); //UPDATE_MODE_DU4
    void Draw(M5EPD_Canvas *canvas);
    void Bind(int16_t event, void (*func_cb)(epdgui_args_vector_t &));
    void UpdateState(int16_t x, int16_t y);
    virtual void Render(JsonVariant data);
    void Init(JsonVariant data);

    M5EPD_Canvas *Canvas();
    M5EPD_Canvas *CanvasPressed();

protected:
    virtual void RenderDescriptionLabel(const char *string);

private:
    void (*_pressed_cb)(epdgui_args_vector_t &args) = NULL;
    void (*_released_cb)(epdgui_args_vector_t &args) = NULL;
    epdgui_args_vector_t _pressed_cb_args;
    epdgui_args_vector_t _released_cb_args;
    int16_t _state = EVENT_NONE;

public:
    M5EPD_Canvas *_Canvas = NULL;
    M5EPD_Canvas *_CanvasPressed = NULL;
};

#endif //__EPDGUI_WIDGET_GRAPHIC_BASE_H