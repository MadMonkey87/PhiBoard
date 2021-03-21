#ifndef __EPDGUI_PAGE_CONTAINER_H
#define __EPDGUI_PAGE_CONTAINER_H

#include "epdgui_base.h"
#include "epdgui_container.h"
#include "epdgui_page_indicator.h"
#include "ArduinoJson.h"
#include "epdgui/epdgui.h"
#include <list>

class EPDGUI_Page_Container : public EPDGUI_Base
{
public:
    static const int16_t INDICATOR_HEIGHT = 60;

    static const int16_t GRID_WIDTH = 2;
    static const int16_t GRID_HEIGHT = 3;
    static const int16_t GRID_MARGIN = 20;

public:
    EPDGUI_Page_Container(int16_t x, int16_t y, int16_t w, int16_t h);
    ~EPDGUI_Page_Container();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_GLD16);
    void Draw(M5EPD_Canvas *canvas);
    void Bind(int16_t event, void (*func_cb)(epdgui_args_vector_t &));
    void UpdateState(int16_t x, int16_t y);
    void EPDGUI_AddComponent(EPDGUI_Base *component, int16_t pageIndex);
    void SetPageIndex(int16_t pageIndex);
    void PropagateWidgets(JsonArray widgets, int16_t width, int16_t offsetY);
    void Init();
    uint32_t GetPageIndex() { return _pageIndex; }

private:
    std::list<EPDGUI_Container *> _pages;
    EPDGUI_Container *GetPageByIndex(int16_t pageIndex);
    EPDGUI_Page_Indicator *_page_indicator;
    int16_t _pageIndex = 0;
    int16_t _size = 0;
};

#endif //__EPDGUI_PAGE_CONTAINER_H