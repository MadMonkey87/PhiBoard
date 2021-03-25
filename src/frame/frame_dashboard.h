#ifndef _FRAME_DASHBOARD_H_
#define _FRAME_DASHBOARD_H_

#include "frame_base.h"
#include "../epdgui/epdgui.h"

class Frame_Dashboard : public Frame_Base
{
public:
    static constexpr const char* APPID = "24184b57-c0d8-4d2a-aa52-9ffd7ad0dc46";
    static const int16_t WIDTH = 540;
    static const int16_t HEIGHT = 960;
    static const int16_t HEADER_HEIGHT = 120;

public:
    Frame_Dashboard();
    ~Frame_Dashboard();
    void run();
    void init(epdgui_args_vector_t &args);

private:
    EPDGUI_Page_Container *_page_container;
    int16_t lastButtonIndex = 0;
    void LoadWidgetsFromJsonFile(String jsonFilePath);
};

#endif //_FRAME_DASHBOARD_H_