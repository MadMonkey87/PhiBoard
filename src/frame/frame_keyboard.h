#ifndef _FRAME_KEYBOARD_H_
#define _FRAME_KEYBOARD_H_

#include "frame_base.h"
#include "../epdgui/epdgui.h"

class Frame_Keyboard : public Frame_Base
{
public:
    static constexpr const char *APPID = "ac5b84cd-2d28-4669-9983-5a352c04cd2f";

public:
    Frame_Keyboard(bool isHorizontal = false);
    ~Frame_Keyboard();
    int run();
    int init(epdgui_args_vector_t &args);

private:
    EPDGUI_Textbox *inputbox;
    EPDGUI_Keyboard *keyboard;
    EPDGUI_Button *key_textclear;
    EPDGUI_Button *key_textsize_plus;
    EPDGUI_Button *key_textsize_reset;
    EPDGUI_Button *key_textsize_minus;
};

#endif //_FRAME_KEYBOARD_H_