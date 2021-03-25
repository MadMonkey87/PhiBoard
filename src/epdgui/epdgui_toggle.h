#ifndef __EPDGUI_Toggle_H
#define __EPDGUI_Toggle_H

#include "epdgui_base.h"

class EPDGUI_Toggle : public EPDGUI_Base
{
public:
    static const int16_t EVENT_NONE = 0;
    static const int16_t EVENT_PRESSED = 1;
    static const int16_t EVENT_RELEASED = 2;

    static const int16_t GROUND_COLOR = 0;
    static const int16_t BORDER_WIDTH = 4;
    static const int16_t BORDER_COLOR = 12;
    static const int16_t BACKGROUND_COLOR = 4;
    static const int16_t KNOB_COLOR = 15;

public:
    EPDGUI_Toggle(int16_t x, int16_t y, int16_t w, int16_t h);
    ~EPDGUI_Toggle();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_DU4);
    void Draw(M5EPD_Canvas *canvas);
    void UpdateTouchState(int16_t x, int16_t y);

    void AddValueChangedEventArgs(uint16_t n, void *arg);
    void BindValueChangedEvent(void (*func_cb)(epdgui_args_vector_t &));

    void BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &));

    boolean GetValue() { return _value != 0; }
    void SetValue(int8_t value);

    M5EPD_Canvas *CanvasNormal();
    M5EPD_Canvas *CanvasPressed();

protected:
    void Render();

private:
    void (*_released_cb)(epdgui_args_vector_t &args) = NULL;
    epdgui_args_vector_t _released_cb_args;
    int16_t _state = EVENT_NONE;
    int8_t _value;

public:
    M5EPD_Canvas *_CanvasNormal = NULL;
    M5EPD_Canvas *_CanvasPressed = NULL;
};

#endif //__EPDGUI_Toggle_H