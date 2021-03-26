#ifndef __EPDGUI_HEADER_H
#define __EPDGUI_HEADER_H

#include "epdgui_base.h"

class EPDGUI_Header : public EPDGUI_Base
{
public:
    static const int16_t GROUND_COLOR = 0;

    static const int16_t TEXT_SIZE = 26;
    static const int16_t FONT_COLOR = 15;
    static const int16_t SEPARATOR_COLOR = 4;
    static const int16_t SEPARATOR_HEIGHT = 1;
    static const int16_t SEPARATOR_HORIZONTAL_MARGIN = 10;

    static const int16_t STATUSBAR_HEIGHT = 40;
    static const int16_t STATUSBAR_BACKGROUND_COLOR = 1;

public:
    static const int16_t EVENT_NONE = 0;
    static const int16_t EVENT_PRESSED = 1;
    static const int16_t EVENT_RELEASED = 2;

public:
    EPDGUI_Header(int16_t x, int16_t y, int16_t w, int16_t h, String title = "", boolean _hasBackButton = true);
    ~EPDGUI_Header();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_GLD16);
    void Draw(M5EPD_Canvas *canvas);
    void BindEvent(int16_t event, void (*func_cb)(epdgui_args_vector_t &));
    void UpdateTouchState(int16_t x, int16_t y);
    void AddArgs(int16_t event, uint16_t n, void *arg);

    void SetTitle(String title);
    String GetTitle() { return _title; }

    M5EPD_Canvas *Canvas();

private:
    virtual void Render();
    void (*_pressed_cb)(epdgui_args_vector_t &args) = NULL;
    void (*_released_cb)(epdgui_args_vector_t &args) = NULL;
    epdgui_args_vector_t _pressed_cb_args;
    epdgui_args_vector_t _released_cb_args;
    int16_t _state = EVENT_NONE;
    String _title;
    int8_t _hasBackButton;

public:
    M5EPD_Canvas *_Canvas = NULL;
};

#endif //__EPDGUI_HEADER_H