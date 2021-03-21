#ifndef __EPDGUI_WIDGET_BASE_H
#define __EPDGUI_WIDGET_BASE_H

#include "../epdgui_base.h"
#include "ArduinoJson.h"

class EPDGUI_Widget_Base: public EPDGUI_Base
{
public:
    static const int16_t EVENT_NONE = 0;
    static const int16_t EVENT_PRESSED = 1;
    static const int16_t EVENT_RELEASED = 2;

    static const int16_t GROUND_COLOR = 0;

    static const bool RENDER_BORDER = true;
    static const int16_t CORNER_ROUNDING = 16;
    static const int16_t BORDER_WIDTH = 2;
    static const int16_t TEXT_SIZE = 26;

    static const int16_t BORDER_COLOR = 15;
    static const int16_t BACKGROUND_COLOR = 0;
    static const int16_t FONT_COLOR = 15;

    static const int16_t RENDER_BACKGROUND_MODE_TOP_LEFT = 0;
    static const int16_t RENDER_BACKGROUND_MODE_TOP = 1;
    static const int16_t RENDER_BACKGROUND_MODE_TOP_RIGHT = 2;
    static const int16_t RENDER_BACKGROUND_MODE_LEFT = 3;
    static const int16_t RENDER_BACKGROUND_MODE_MIDDLE = 4;
    static const int16_t RENDER_BACKGROUND_MODE_RIGHT = 5;
    static const int16_t RENDER_BACKGROUND_MODE_BOTTOM_LEFT = 6;
    static const int16_t RENDER_BACKGROUND_MODE_BOTTOM_MIDDLE = 7;
    static const int16_t RENDER_BACKGROUND_MODE_BOTTOM_RIGHT = 8;
    static const int16_t RENDER_BACKGROUND_MODE_MIDDLE_VERTICAL = 9;
    static const int16_t RENDER_BACKGROUND_MODE_MIDDLE_HORIZONTAL = 10;
    static const int16_t RENDER_BACKGROUND_MODE_FULL = 11;
    static const int16_t RENDER_BACKGROUND_MODE_FULL_WITHOUT_TOP = 12;
    static const int16_t RENDER_BACKGROUND_MODE_FULL_WITHOUT_BOTTOM = 13;
    static const int16_t RENDER_BACKGROUND_MODE_FULL_WITHOUT_LEFT = 14;
    static const int16_t RENDER_BACKGROUND_MODE_FULL_WITHOUT_RIGHT = 15;

public:
    EPDGUI_Widget_Base(int16_t x, int16_t y, int16_t w, int16_t h);
    ~EPDGUI_Widget_Base();
    //void Draw(m5epd_update_mode_t mode = UPDATE_MODE_GLD16); //UPDATE_MODE_GL16 //UPDATE_MODE_DU4
    //void Draw(M5EPD_Canvas* canvas);
    virtual void Render(JsonVariant data);
    void Init(JsonVariant data);

protected:
    virtual void RenderDescriptionLabel(M5EPD_Canvas* canvas, const char *string);
    void RenderBackground(int16_t mode, M5EPD_Canvas* canvas, bool revertable);
};


#endif //__EPDGUI_WIDGET_BASE_H