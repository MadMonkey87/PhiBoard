#ifndef __PHI_WIDGET_Progress_H
#define __PHI_WIDGET_Progress_H

#include "phi_widget_graphic_base.h"
#include "ArduinoJson.h"

struct Widget_Progress_Definition : Widget_Base_Definition
{
    String Description;
    PhiAction_Definition *PhiAction;
};

class PHI_Widget_Progress : public PHI_Widget_Graphic_Base
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
    PHI_Widget_Progress(int16_t x, int16_t y, int16_t w, int16_t h, Widget_Progress_Definition *definition);
    void Render();

protected:
    Widget_Progress_Definition *_definition;
    PhiAction_Definition *GetPhiAction();

private:
    void RenderInternal();
    void RenderGauge(M5EPD_Canvas *canvas, int16_t x, int16_t y, int16_t outerRadius, int16_t innerRadius, int16_t value, int16_t minValue, int16_t maxValue, float startRadian, float endRadian, int16_t color, bool roundBegin, bool roundEnd);
};

#endif //__PHI_WIDGET_Progress_H