#ifndef __EPDGUI_WIDGET_Progress_H
#define __EPDGUI_WIDGET_Progress_H

#include "epdgui_widget_graphic_base.h"
#include "ArduinoJson.h"

class EPDGUI_Widget_Progress : public EPDGUI_Widget_Graphic_Base
{
public:
    static const int16_t MARGIN = 20;
    static const int16_t OUTER_BORDER_WIDTH = 2;
    static const int16_t INNER_BORDER_WIDTH = 2;
    static const int16_t OUTER_BORDER_COLOR = 15;
    static const int16_t INNER_BORDER_COLOR = 15;
    static const int16_t OUTER_BACKGROUND_COLOR = 2;
    static const int16_t INNER_BACKGROUND_COLOR = 0;
    static const int16_t INNER_RADIUS_RELATIVE = 30;
    static const int16_t FILL_COLOR = 15;
    static const int16_t FILL_ROUND_BEGIN = false;
    static const int16_t FILL_ROUND_END = true;

public:
    EPDGUI_Widget_Progress(int16_t x, int16_t y, int16_t w, int16_t h);
    void Render(JsonVariant data);

private:
    void Render();
    void RenderGauge(M5EPD_Canvas *canvas, int16_t x, int16_t y, int16_t outerRadius, int16_t innerRadius, int16_t value, int16_t minValue, int16_t maxValue, float startRadian, float endRadian, int16_t color, bool roundBegin, bool roundEnd);
};

#endif //__EPDGUI_WIDGET_Progress_H