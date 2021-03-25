#ifndef __EPDGUI_Slider_H
#define __EPDGUI_Slider_H

#include "epdgui_base.h"

class EPDGUI_Slider : public EPDGUI_Base
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

    static const int16_t MARGIN = 20; // usefull to increase the touch area around the controll

public:
    EPDGUI_Slider(int16_t x, int16_t y, int16_t w, int16_t h);
    ~EPDGUI_Slider();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_DU4);
    void Draw(M5EPD_Canvas *canvas);
    void UpdateTouchState(int16_t x, int16_t y);

    void AddValueChangedEventArgs(uint16_t n, void *arg);
    void BindValueChangedEvent(void (*func_cb)(epdgui_args_vector_t &));

    void BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &));

    int16_t GetValue() { return _value; }
    void SetValue(int16_t value);

    M5EPD_Canvas *Canvas();

protected:
    void Render();

private:
    void (*_released_cb)(epdgui_args_vector_t &args) = NULL;
    epdgui_args_vector_t _released_cb_args;
    int16_t _state = EVENT_NONE;

    int16_t _value;
    int16_t _minValue = 0;
    int16_t _maxValue = 100;
    int16_t _min_x;
    int16_t _max_x;

public:
    M5EPD_Canvas *_Canvas = NULL;
};

#endif //__EPDGUI_Slider_H