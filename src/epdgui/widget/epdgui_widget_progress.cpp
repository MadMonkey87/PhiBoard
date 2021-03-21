#include "epdgui_widget_progress.h"

EPDGUI_Widget_Progress::EPDGUI_Widget_Progress(int16_t x, int16_t y, int16_t w, int16_t h) : EPDGUI_Widget_Graphic_Base(x, y, w, h, true, true)
{
}

void EPDGUI_Widget_Progress::Render(JsonVariant data)
{
    EPDGUI_Widget_Graphic_Base::Render(data);

    this->Render();
}

void EPDGUI_Widget_Progress::Render()
{
    bool portrait = _h > _w || _h > 240;
    int16_t OFFSET_Y = portrait ? 0 : -20;
    int16_t OUTER_RADIUS = (portrait ? _w : _h) / 2 - MARGIN + OFFSET_Y;
    int16_t INNER_RADIUS = OUTER_RADIUS - (portrait ? _w : _h) / 240 * INNER_RADIUS_RELATIVE;

    _Canvas->fillCircle(_w / 2, _h / 2 + OFFSET_Y, OUTER_RADIUS, OUTER_BORDER_COLOR);
    _Canvas->fillCircle(_w / 2, _h / 2 + OFFSET_Y, OUTER_RADIUS - OUTER_BORDER_WIDTH, OUTER_BACKGROUND_COLOR);
    RenderGauge(_Canvas, _w / 2, _h / 2 + OFFSET_Y, OUTER_RADIUS - OUTER_BORDER_WIDTH, INNER_RADIUS + INNER_BORDER_WIDTH, 65, 0, 100, (float)M_PI, (float)M_PI * 3.0, FILL_COLOR, FILL_ROUND_BEGIN, FILL_ROUND_END);
    _Canvas->fillCircle(_w / 2, _h / 2 + OFFSET_Y, INNER_RADIUS + INNER_BORDER_WIDTH, INNER_BORDER_COLOR);
    _Canvas->fillCircle(_w / 2, _h / 2 + OFFSET_Y, INNER_RADIUS, INNER_BACKGROUND_COLOR);

    _CanvasPressed->fillCircle(_w / 2, _h / 2 + OFFSET_Y, OUTER_RADIUS, OUTER_BORDER_COLOR);
    _CanvasPressed->fillCircle(_w / 2, _h / 2 + OFFSET_Y, OUTER_RADIUS - OUTER_BORDER_WIDTH, OUTER_BACKGROUND_COLOR);
    RenderGauge(_CanvasPressed, _w / 2, _h / 2 + OFFSET_Y, OUTER_RADIUS - OUTER_BORDER_WIDTH, INNER_RADIUS + INNER_BORDER_WIDTH, 65, 0, 100, (float)M_PI, (float)M_PI * 3.0, FILL_COLOR, FILL_ROUND_BEGIN, FILL_ROUND_END);
    _CanvasPressed->fillCircle(_w / 2, _h / 2 + OFFSET_Y, INNER_RADIUS + INNER_BORDER_WIDTH, INNER_BORDER_COLOR);
    _CanvasPressed->fillCircle(_w / 2, _h / 2 + OFFSET_Y, INNER_RADIUS, INNER_BACKGROUND_COLOR);

    String value = "65%";
    _Canvas->setTextSize(TEXT_SIZE);
    _Canvas->setTextColor(FONT_COLOR);
    _Canvas->setTextDatum(MC_DATUM);
    _Canvas->drawString(value.c_str(), _w / 2, _h / 2 + OFFSET_Y);

    _CanvasPressed->setTextSize(TEXT_SIZE);
    _CanvasPressed->setTextColor(FONT_COLOR);
    _CanvasPressed->setTextDatum(MC_DATUM);
    _CanvasPressed->drawString(value.c_str(), _w / 2, _h / 2 + OFFSET_Y);

    String description = "FooBar"; //data["description"];
    if (portrait)
    {
        _CanvasPressed->setTextSize(TEXT_SIZE);
        _CanvasPressed->setTextColor(FONT_COLOR);
        _CanvasPressed->setTextDatum(MC_DATUM);
        _CanvasPressed->drawString(description, _w / 2, _h / 2 + 35);

        _Canvas->setTextSize(TEXT_SIZE);
        _Canvas->setTextColor(FONT_COLOR);
        _Canvas->setTextDatum(MC_DATUM);
        _Canvas->drawString(description, _w / 2, _h / 2 + 35);
    }
    else
    {
        RenderDescriptionLabel(description.c_str());
    }
}

void EPDGUI_Widget_Progress::RenderGauge(M5EPD_Canvas *canvas, int16_t x, int16_t y, int16_t outerRadius, int16_t innerRadius, int16_t value, int16_t minValue, int16_t maxValue, float startRadian, float endRadian, int16_t color, bool roundBegin, bool roundEnd)
{
    // scale main/max/value s.t there are enough lines drawn for a solid fill
    int16_t necessary_iterations = outerRadius * 3.5 + 325;
    float iteration_scale = necessary_iterations / (maxValue - minValue);

    minValue *= iteration_scale;
    maxValue *= iteration_scale;
    value *= iteration_scale;

    for (int a = minValue; a <= value; a++)
    {
        float i = ((a - minValue) * (endRadian - startRadian) / (maxValue - minValue) + startRadian);
        int16_t xp1 = x + (sin(i) * innerRadius);
        int16_t yp1 = y - (cos(i) * innerRadius);
        int16_t xp2 = x + (sin(i) * outerRadius);
        int16_t yp2 = y - (cos(i) * outerRadius);
        canvas->drawLine(xp1, yp1, xp2, yp2, color);

        if (a == minValue && roundBegin || a == value && roundEnd)
        {
            int16_t xp3 = x + (sin(i) * (innerRadius + (outerRadius - innerRadius) / 2));
            int16_t yp3 = y - (cos(i) * (innerRadius + (outerRadius - innerRadius) / 2));

            canvas->fillCircle(xp3, yp3, (outerRadius - innerRadius) / 2, color);
        }
    }
}