#ifndef _FRAME_SETTING_H_
#define _FRAME_SETTING_H_

#include "frame_base.h"
#include "../epdgui/epdgui.h"

class Frame_Setting : public Frame_Base
{
public:
    static constexpr const char *APPID = "ebb592ec-f2ed-456a-b6e4-12b201153e21";

public:
    Frame_Setting();
    ~Frame_Setting();
    int init(epdgui_args_vector_t &args);

private:
    EPDGUI_Button *_key_shutdown;
    EPDGUI_Button *_key_restart;
    EPDGUI_Button *_key_syncntp;

    EPDGUI_Button *key_timezone_plus;
    EPDGUI_Button *key_timezone_reset;
    EPDGUI_Button *key_timezone_minus;
    int _timezone;
    M5EPD_Canvas *_timezone_canvas;
};

#endif //_FRAME_SETTING_H_