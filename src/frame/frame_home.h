#ifndef _FRAME_HOME_H_
#define _FRAME_HOME_H_

#include "frame_base.h"
#include "../epdgui/epdgui.h"

class Frame_Home : public Frame_Base
{
public:
    static constexpr const char *APPID = "6356d87c-6114-4a29-aa9f-62b0340c406f";

public:
    static const int16_t WIDTH = 540;
    static const int16_t HEIGHT = 960;
    static const int16_t HEADER_HEIGHT = 120;

public:
    Frame_Home();
    ~Frame_Home();
    void run();
    void init(epdgui_args_vector_t &args);

private:
    EPDGUI_Page_Container *_page_container;
    int16_t lastButtonIndex = 0;
};

#endif //_FRAME_HOME_H_