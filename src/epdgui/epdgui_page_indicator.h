#ifndef __EPDGUI_PAGE_INDICATOR_H
#define __EPDGUI_PAGE_INDICATOR_H

#include "epdgui_base.h"

class EPDGUI_Page_Indicator : public EPDGUI_Base
{
public:
    static const int16_t GROUND_COLOR = 0;

    static const int16_t INDICATOR_SPACING = 10;

    static const int16_t INDICATOR_RADIUS = 10;
    static const int16_t INDICATOR_BORDER_COLOR = 15;
    static const int16_t INDICATOR_BACKGROUND_COLOR = 2;
    static const int16_t INDICATOR_BORDER_WIDTH = 2;

    static const int16_t INDICATOR_SELECTED_RADIUS = 12;
    static const int16_t INDICATOR_SELECTED_BORDER_COLOR = 15;
    static const int16_t INDICATOR_SELECTED_BACKGROUND_COLOR = 12;
    static const int16_t INDICATOR_SELECTED_BORDER_WIDTH = 4;

public:
    EPDGUI_Page_Indicator(int16_t x, int16_t y, int16_t w, int16_t h, int16_t size);
    ~EPDGUI_Page_Indicator();
    void Draw(m5epd_update_mode_t mode = UPDATE_MODE_GLD16);
    void Draw(M5EPD_Canvas *canvas);
    void Bind(int16_t event, void (*func_cb)(epdgui_args_vector_t &));
    void UpdateState(int16_t x, int16_t y);
    void SetPageIndex(int16_t pageIndex);
    M5EPD_Canvas *Canvas();

public:
    M5EPD_Canvas *_Canvas = NULL;

private:
    int16_t _size;
    int16_t _index;
    void Render();
};

#endif //__EPDGUI_PAGE_INDICATOR_H