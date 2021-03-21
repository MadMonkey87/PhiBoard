#ifndef _FRAME_COMPARE_H_
#define _FRAME_COMPARE_H_

#include "frame_base.h"
#include "../epdgui/epdgui.h"

class Frame_Compare : public Frame_Base
{
public:
    static constexpr const char *APPID = "9e1d635a-6836-4444-a22f-8336f631bf96";

public:
    Frame_Compare();
    ~Frame_Compare();
    int init(epdgui_args_vector_t &args);
    int run();

private:
    EPDGUI_Button *_key_updatemode[8];
    uint8_t _update_flag;
    M5EPD_Canvas *_canvas;
    M5EPD_Canvas *_canvas_time;
};

#endif //_FRAME_COMPARE_H_