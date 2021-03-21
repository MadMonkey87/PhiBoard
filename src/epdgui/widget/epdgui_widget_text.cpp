#include "epdgui_widget_text.h"

EPDGUI_Widget_Text::EPDGUI_Widget_Text(int16_t x, int16_t y, int16_t w, int16_t h): 
EPDGUI_Widget_Graphic_Base(x, y, w, h, true, true)
{

}

void EPDGUI_Widget_Text::Render(JsonVariant data)
{
    EPDGUI_Widget_Graphic_Base::Render(data);

    String description = data["description"];
    String value = data["value"];
    String hint = data["hint"];

    this->_Canvas->setTextSize(TEXT_SIZE);
    this->_Canvas->setTextColor(FONT_COLOR);
    this->_Canvas->setTextDatum(MC_DATUM);
    this->_Canvas->drawString(hint.c_str(),  _w/2, 35);

    this->_CanvasPressed->setTextSize(TEXT_SIZE);
    this->_CanvasPressed->setTextColor(FONT_COLOR);
    this->_CanvasPressed->setTextDatum(MC_DATUM);
    this->_CanvasPressed->drawString(hint.c_str(),  _w/2, 35);

    this->_Canvas->setTextSize(TEXT_SIZE);
    this->_Canvas->setTextColor(FONT_COLOR);
    this->_Canvas->setTextDatum(MC_DATUM);
    this->_Canvas->drawString(value.c_str(),  _w/2, _h/2);

    this->_CanvasPressed->setTextSize(TEXT_SIZE);
    this->_CanvasPressed->setTextColor(FONT_COLOR);
    this->_CanvasPressed->setTextDatum(MC_DATUM);
    this->_CanvasPressed->drawString(value.c_str(),  _w/2, _h/2);

    RenderDescriptionLabel(description.c_str());
}